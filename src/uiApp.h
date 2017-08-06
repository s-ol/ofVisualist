#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxMidi.h"
// #include "effectApp.h"
#include "videosource.h"
#include "farbblut.h"
#include "midiMapper.h"

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
    void newMidiMessage(ofxMidiMessage& eventArgs);

  protected:
//     shared_ptr<EffectApp> effect;
    ofPlanePrimitive      preview;
    ofxPanel              panel;
    ofxMidiIn*            midiIn;
    Farbblut              farbblut;
    IVideoSource*         source;
    MidiMapper*           mapper;
};
