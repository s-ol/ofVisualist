#include "uiApp.h"

// UiApp::UiApp(shared_ptr<EffectApp> effect)
//   : ofBaseApp(), effect(effect), plane(400, 300, 10, 10) {
UiApp::UiApp()
  : ofBaseApp(), preview(ofGetWidth() - 220, ofGetHeight(), 10, 10) {
  preview.mapTexCoords(0, 0, 800, 600);
  preview.setPosition((ofGetWidth() + 220) / 2, ofGetHeight() / 2, 0);
  source = new ExternalVideoSource();
}

void UiApp::setup() {
  panel.setup(farbblut.parameters);
}

void UiApp::update(){
  source->update();
  farbblut.update();
}

void UiApp::draw(){
  ofBackgroundGradient(ofColor::white, ofColor::gray);

  ofSetColor(0x0);
  preview.draw();
  farbblut.draw(source->getTexture(), preview);
  panel.draw();
}

void UiApp::windowResized(int w, int h) {
  preview.set(w - 220, h, 10, 10);
  preview.setPosition((w + 220) / 2, h / 2, 0);
}

void UiApp::exit() {
}

void UiApp::keyPressed(int key) {
  if (key == 'x') {
    /*
    if (!effect) {
      ofGLWindowSettings outputSettings;
      outputSettings.width = 600;
      outputSettings.height = 400;
      outputSettings.windowMode = OF_FULLSCREEN;
      auto outputWindow = ofCreateWindow(outputSettings);
      effect = make_shared<EffectApp>();
      ofRunApp(outputWindow, effect);
    }
    */
  }
}
