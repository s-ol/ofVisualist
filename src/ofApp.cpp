#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  for (int i = 0; i < COLOR_STEPS; ++i) {
    colors[i] = ofColor::fromHsb(255, 180, 75 + (i * (float) 177) / COLOR_STEPS);
  };

  ofBackground(255,255,255);
  ofSetVerticalSync(true);
  frameByframe = false;

  // Uncomment this to show movies with alpha channels
  // fingerMovie.setPixelFormat(OF_PIXELS_RGBA);

  fingerMovie.load("movies/fingers.mov");
  fingerMovie.setLoopState(OF_LOOP_NORMAL);
  fingerMovie.play();
}

//--------------------------------------------------------------
void ofApp::update(){
  fingerMovie.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

  ofSetHexColor(0xFFFFFF);
  fingerMovie.draw(20,20);

  ofSetHexColor(0x000000);
  ofPixels & pixels = fingerMovie.getPixels();

  int vidWidth = pixels.getWidth();
  int vidHeight = pixels.getHeight();
  int nChannels = pixels.getNumChannels();

  offset += speed * ofGetLastFrameTime() * COLOR_STEPS;

  // let's move through the "RGB(A)" char array
  // using the red pixel to control the size of a circle.
  for (int i = 4; i < vidWidth; ++i){
    for (int j = 4; j < vidHeight; ++j){
      unsigned char *pix = &pixels[(j * 320 + i)*nChannels];
      float luminance = (pix[0] / 256.0f * 0.3f) + (pix[1] / 256.0f * 0.59f) + (pix[2] / 256.0f * 0.11f);
      unsigned char index = luminance * COLOR_STEPS;
      ofSetHexColor(colors[(index + (int)offset) % COLOR_STEPS].getHex());
      ofDrawLine(400 + i, 20 + j, 400 + i, 21 + j);
    }
  }

  ofSetHexColor(0x000000);
  ofDrawBitmapString("press f to change",20,320);
  if(frameByframe) ofSetHexColor(0xCCCCCC);
  ofDrawBitmapString("mouse speed position",20,340);
  if(!frameByframe) ofSetHexColor(0xCCCCCC); else ofSetHexColor(0x000000);
  ofDrawBitmapString("keys <- -> frame by frame " ,190,340);
  ofSetHexColor(0x000000);

  ofDrawBitmapString("frame: " + ofToString(fingerMovie.getCurrentFrame()) + "/"+ofToString(fingerMovie.getTotalNumFrames()),20,380);
  ofDrawBitmapString("duration: " + ofToString(fingerMovie.getPosition()*fingerMovie.getDuration(),2) + "/"+ofToString(fingerMovie.getDuration(),2),20,400);
  ofDrawBitmapString("speed: " + ofToString(speed,2),20,420);
  ofDrawBitmapString("offset: " + ofToString(offset,2),20,440);

  if(fingerMovie.getIsMovieDone()){
    ofSetHexColor(0xFF0000);
    ofDrawBitmapString("end of movie",20,440);
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
  switch(key){
    case 'f':
      frameByframe=!frameByframe;
      fingerMovie.setPaused(frameByframe);
      break;
    case OF_KEY_LEFT:
      fingerMovie.previousFrame();
      break;
    case OF_KEY_RIGHT:
      fingerMovie.nextFrame();
      break;
    case '0':
      fingerMovie.firstFrame();
      break;
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
  if(!frameByframe){
    int width = ofGetWidth();
    float pct = (float)x / (float)width;
    speed = (pct - 0.5) * 10;
  }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
  if(!frameByframe){
    int width = ofGetWidth();
    float pct = (float)x / (float)width;
    fingerMovie.setPosition(pct);
  }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
  if(!frameByframe){
    fingerMovie.setPaused(true);
  }
}


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
  if(!frameByframe){
    fingerMovie.setPaused(false);
  }
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
