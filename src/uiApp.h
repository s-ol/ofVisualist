#pragma once

#include "ofMain.h"
#include "ofxGui.h"
// #include "effectApp.h"
#include "videosource.h"
#include "farbblut.h"

class UiApp : public ofBaseApp {
  public:
//    UiApp(shared_ptr<EffectApp> effect);
    UiApp();
    void setup();
    void update();
    void draw();
    void exit();
    void windowResized(int w, int h);
    void keyPressed(int key);

  protected:
//     shared_ptr<EffectApp> effect;
    ofPlanePrimitive      preview;
    ofxPanel              panel;
    Farbblut              farbblut;
    IVideoSource*         source;
};
