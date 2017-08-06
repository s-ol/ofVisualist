#pragma once

#include "ofMain.h"
#include "ofxMidi.h"

class MidiMapper : public ofxMidiListener {
  public:
    MidiMapper(ofxMidiIn* midiIn, ofParameterGroup& parameters, map<int, string> mapping);

    void newMidiMessage(ofxMidiMessage& message);

    map<int, string>  mapping;
    ofParameterGroup& parameters;
};
