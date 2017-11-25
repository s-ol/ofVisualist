#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  for (int i = 0; i < COLOR_STEPS; ++i)
    colors[i] = ofFloatColor::fromHsb(0, 0, (float)i / COLOR_STEPS);

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
  if (ofGetElapsedTimef() > nextMidiFix)
    fixMidi();
  ofBackground(0, 0, 0);
  vidGrabber.update();
  if (!paused)
    time += speed * ofGetLastFrameTime() * COLOR_STEPS;
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofSetHexColor(0xffffff);

  vidGrabber.getTexture().bind();
  shader.begin();
  shader.setUniform4fv("colors", (float*)colors, 8);
  shader.setUniform1f("offset", time + offset);
  shader.setUniform1f("colMix", colMix);
  shader.setUniform1f("lumMix", lumMix);
  shader.setUniform1f("lumOff", lumOff);
  shader.setUniform1f("lumTLo", lumTLo);
  shader.setUniform1f("lumTHi", lumTHi);
  plane.draw();
  shader.end();
  vidGrabber.getTexture().unbind();
}

void ofApp::newMidiMessage(ofxMidiMessage& msg) {
  if (msg.status == MIDI_CONTROL_CHANGE) {
    float value = msg.value / 127.0f;
    float cent = (msg.value - 64) / 64.0f;
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
      // rotation controls
      case 9: paused = !paused; break;  // freeze
      case 10: speed = -speed; break;   // reverse
      case 11: time += 1; break;        // jump

      // color modes
      case 25: // b+w
        for (int i = 0; i < COLOR_STEPS; ++i)
          colors[i] = ofFloatColor::fromHsb(0, 0, (float)i / COLOR_STEPS);
        break;
      case 26: // black-to-red
        for (int i = 0; i < COLOR_STEPS; ++i)
          colors[i] = ofFloatColor::fromHsb(0, 1, (float)i / COLOR_STEPS);
        break;
      case 27: // greenblue
        for (int i = 0; i < COLOR_STEPS; ++i)
          colors[i] = ofFloatColor::fromHsb(0.4 + 0.2 * sin((float)i / COLOR_STEPS * 24), 0.6, 0.6);
        break;
      case 28: // rainbow
        for (int i = 0; i < COLOR_STEPS; ++i)
          colors[i] = ofFloatColor::fromHsb((float)i / COLOR_STEPS, 0.6, 0.6);
        break;
    }
  }
}

//--------------------------------------------------------------
void ofApp::exit() {
}

void ofApp::fixMidi() {
  nextMidiFix = ofGetElapsedTimef() + 0.2f;
  if (midiIn->getPortList().size() <= 0) {
    if (!midiBroken) {
      midiIn->closePort();
      midiIn->removeListener(this);
      midiBroken = true;
    }
  } else if (midiBroken) {
    midiIn = new ofxMidiIn();
    midiIn->openPort(0);
    midiIn->addListener(this);
    midiBroken = false;
  }
}

void ofApp::keyPressed(int key) {
  if (key == 'r') {
    midiIn->closePort();
    midiIn->removeListener(this);
    midiIn = new ofxMidiIn();
    midiIn->openPort(0);
    midiIn->addListener(this);
    ofLogNotice() << "restarted";
  } else if (key == 'f') {
    ofToggleFullscreen();
  } else if (key >= '0' && key <= '9') {
    int id = key - '0';
    vidGrabber = ofVideoGrabber();
    vidGrabber.setDeviceID(id);
    vidGrabber.setDesiredFrameRate(30);
    vidGrabber.initGrabber(CAPTURE_RES);
  }
}