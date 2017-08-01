#pragma once

#include "ofMain.h"
#include "effectApp.h"

#define COLOR_STEPS 8
#define CAPTURE_RES 720,576
#define SCREEN_RES 1920,1080

class UiApp : public ofBaseApp {
  public:
    UiApp(shared_ptr<EffectApp> effect);
    void setup();
    void update();
    void draw();
    void exit();
    void keyPressed(int key);

  protected:
    shared_ptr<EffectApp> effect;
};
