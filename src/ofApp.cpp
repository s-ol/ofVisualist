#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  for (int i = 0; i < COLOR_STEPS; ++i) {
    colors[i] = ofFloatColor::fromHsb((float)i / COLOR_STEPS, 0.6, 0.6);
  };

  ofBackground(255, 255, 255);
  ofSetVerticalSync(false);

  vector<ofVideoDevice> devices = vidGrabber.listDevices();

  for (int i = 0; i < devices.size(); i++) {
    if (devices[i].bAvailable) {
      ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
      ofLogNotice() << "formats: " << devices[i].formats.size();
      for (int f = 0; f < devices[i].formats.size(); f++) {
        auto format = devices[i].formats[f];
        ofLogNotice() << "- " << format.width << "x" << format.height << " f " << format.framerates[0];
      }
    } else {
      //log the device and note it as unavailable
      ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
    }
  }

  vidGrabber.setDeviceID(0);
  vidGrabber.setDesiredFrameRate(30);
  vidGrabber.initGrabber(CAPTURE_RES);
  shader.load("shader");

  plane.set(SCREEN_RES, 10, 10);
  plane.mapTexCoords(0, 0, vidGrabber.getWidth(), vidGrabber.getHeight());
  plane.setPosition(ofGetWidth() / 2, ofGetHeight() / 2, 0);

  midiIn = new ofxMidiIn();
  midiIn->listPorts();
  midiIn->openPort(0);
  midiIn->addListener(this);
}

//--------------------------------------------------------------
void ofApp::update(){
  ofBackground(0, 0, 0);
  vidGrabber.update();
  if (!paused)
    time += speed * ofGetLastFrameTime() * COLOR_STEPS;
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofSetHexColor(0xffffff);

  vidGrabber.getTextureReference().bind();

  shader.begin();
  shader.setUniform4fv("colors", (float*)colors, 8);
  shader.setUniform1f("offset", time + offset);
  shader.setUniform1f("colMix", colMix);
  shader.setUniform1f("lumMix", lumMix);
  shader.setUniform1f("lumOff", lumOff);
  shader.setUniform1f("lumTLo", lumTLo);
  shader.setUniform1f("lumTHi", lumTHi);
  shader.setUniform1i("stepMode", stepMode ? 1 : 0);
  plane.draw();
  shader.end();
  vidGrabber.getTextureReference().unbind();
}

void ofApp::newMidiMessage(ofxMidiMessage& msg) {
  if (msg.status == MIDI_CONTROL_CHANGE) {
    float value = msg.value / 127.0f;
    float cent = (msg.value - 64) / 64.0f;;
    switch (msg.control) {
      case 27: lumMix = value; break;
      case 28: colMix = value; break;
      case 41: lumTLo = value; break;
      case 42: lumTHi = value; break;
      case 43: lumOff = value; break;
      case 47: speed = cent * 5; break;
      case 48: offset = cent * 2; break;
    }
  } else if (msg.status == MIDI_NOTE_ON) {
    switch (msg.pitch) {
      case 9: paused = !paused; break;
      case 10: stepMode = !stepMode; break;
    }
  }
}

//--------------------------------------------------------------
void ofApp::exit() {
}

void ofApp::keyPressed(int key) {
  if (key != 'r') return;
    midiIn->closePort();
      midiIn->removeListener(this);

      midiIn = new ofxMidiIn();
  midiIn->openPort(0);
  midiIn->addListener(this);
  ofLogNotice() << "restarted";
}
