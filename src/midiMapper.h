#pragma once

#include "ofMain.h"
#include "ofxMidi.h"

class MidiMapper : public ofxMidiListener {
  public:
    MidiMapper(ofxMidiIn* midiIn, ofParameterGroup& parameters, map<int, string> mapping);

    void newMidiMessage(ofxMidiMessage& eventArgs);

    map<int, string>  mapping;
    ofParameterGroup& parameters;
};
