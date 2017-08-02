#pragma once

#include "ofMain.h"

#define COLOR_STEPS 8

class Farbblut {
  public:
    Farbblut();
    void update();
    void draw(ofTexture& texture, ofPlanePrimitive& plane);

    ofParameter<float> speed, time, offset, colMix, lumMix, lumOff, lumBse, bandSt, bandWt;
    ofParameter<bool> paused;
    ofParameterGroup parameters;

  protected:
    ofFloatColor        colors[COLOR_STEPS];
    ofShader            shader;
};
