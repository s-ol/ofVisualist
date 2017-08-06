#pragma once

#include "ofMain.h"
#include "ofxMidi.h"

struct SMPTETime {
  int hours;
  int minutes;
  int seconds;
  int frames;
  int numFrames = 30;
  void updateNumFrames() {
    switch (hours >> 5) {
      case 0: numFrames = 24; break;
      case 1: numFrames = 25; break;
      case 2:
        numFrames = 30;
        ofLogWarning() << "SMPTE Type 2 (30fps, frame-drop) not supported!";
        break;
      case 3: numFrames = 30; break;
      default:
        numFrames = 100;
        ofLogError() << "Unknown SMPTE Type";
        break;
    }
    hours &= 0x1f;
  };
  void trace(string ref) {
    ofLogNotice(ref) << hours << ":" << minutes << ":" << seconds << ":" << frames << " (" << numFrames << ")";
  };
};

class IVideoSource {
  public:
    virtual void update() = 0;
    virtual ofTexture& getTexture() = 0;
};

class ExternalVideoSource : public IVideoSource {
  public:
    ExternalVideoSource();
    void        update();
    ofTexture&  getTexture();

  protected:
    ofVideoGrabber grabber;
};

class SyncedVideoSource : public IVideoSource, ofxMidiListener {
  public:
    SyncedVideoSource(string filename, ofxMidiIn *midiIn);
    void        update();
    ofTexture&  getTexture();

    void        newMidiMessage(ofxMidiMessage& message);

  protected:
    ofVideoPlayer player;
    SMPTETime     target;
};
