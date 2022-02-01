#include "midiMapper.h"

MidiMapper::MidiMapper(ofxMidiIn* midiIn, ofParameterGroup& parameters, map<int, string> mapping)
  : mapping(mapping), parameters(parameters) {
  midiIn->addListener(this);
};

void MidiMapper::newMidiMessage(ofxMidiMessage& msg) {
  if (msg.status != MIDI_CONTROL_CHANGE) return;
  // if (channel > 0 && msg.channel != channel) return;

  auto key = mapping.find(msg.control);
  if (key == mapping.end()) return;
  ofParameter<float>& param = parameters.getFloat(key->second);
  param.set(ofLerp(param.getMin(), param.getMax(), msg.value / 127.0f));
}
