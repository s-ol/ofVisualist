#include "uiApp.h"

UiApp::UiApp(shared_ptr<EffectApp> effect) : ofBaseApp(), effect(effect) {
}

//--------------------------------------------------------------
void UiApp::setup() {
}

//--------------------------------------------------------------
void UiApp::update(){
}

//--------------------------------------------------------------
void UiApp::draw(){
  ofSetHexColor(0xffffff);
  ofRectangle(10, 10, 200, 200);
}

//--------------------------------------------------------------
void UiApp::exit() {
}

void UiApp::keyPressed(int key) {
  if (key == 'x') {
    if (!effect) {
      ofGLWindowSettings outputSettings;
      outputSettings.width = 600;
      outputSettings.height = 400;
      outputSettings.windowMode = OF_FULLSCREEN;
      auto outputWindow = ofCreateWindow(outputSettings);
      effect = make_shared<EffectApp>();
      ofRunApp(outputWindow, effect);
    }
  }
  ofLogNotice() << "restarted";
}
