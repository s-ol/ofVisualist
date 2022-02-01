#pragma once

#include "ofMain.h"
#include "ofxMidi.h"

#define COLOR_STEPS 8
#define CAPTURE_RES 720,576
#define SCREEN_RES 1920,1080

class EffectApp : public ofBaseApp, public ofxMidiListener {
  public:
    void setup();
    void update();
    void draw();
    void exit();
    void keyPressed(int key);

    void newMidiMessage(ofxMidiMessage& eventArgs);

    float               speed  = 0.1f;
    float               time   = 0.0f;
    float               offset = 0.0f;
    float               colMix = 0.5f;
    float               lumMix = 0.5f;
    float               lumOff = 0.0f;
    float               lumTLo = 0.0f;
    float               lumTHi = 1.0f;
    bool                stepMode = false;
    bool                paused = false;

    ofxMidiIn*          midiIn;
    ofFloatColor        colors[COLOR_STEPS];
    ofVideoGrabber      vidGrabber;
    ofShader            shader;
    ofPlanePrimitive    plane;
};
