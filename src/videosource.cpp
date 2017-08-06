#include "videosource.h"

ExternalVideoSource::ExternalVideoSource() {
  grabber.setDeviceID(0);
  grabber.setDesiredFrameRate(30);
  grabber.initGrabber(800, 600);
}

void ExternalVideoSource::update() {
  grabber.update();
}

ofTexture& ExternalVideoSource::getTexture() {
  return grabber.getTexture();
}

//

SyncedVideoSource::SyncedVideoSource(string filename, ofxMidiIn* midiIn) {
  player.load(filename);
  player.setLoopState(OF_LOOP_NORMAL);
  player.play();
  midiIn->addListener(this);
}

void SyncedVideoSource::update() {
  float delta = target - player.getPosition() * player.getDuration();
  target.trace();

  if (delta > 0.3f || delta < -0.3f) {
    ofLogNotice("JUMP") << (float)target << " - " << (player.getPosition() * player.getDuration()) << " / ";
    player.setSpeed(1.0f);
    player.setPosition(target / player.getDuration());
  } else if (delta > 0.05f || delta < -0.05f) {
    ofLogNotice("speed") << 1 + delta / 10.0f;
    player.setSpeed(1 + delta / 10.0f);
  }
  player.update();
}

ofTexture& SyncedVideoSource::getTexture() {
  return player.getTexture();
}


void SyncedVideoSource::newMidiMessage(ofxMidiMessage& msg) {
  switch (msg.status) {
    case MIDI_START:
      player.firstFrame();
    case MIDI_CONTINUE:
      player.setPaused(false);
      break;
    case MIDI_STOP:
      player.setPaused(true);
      break;
    case MIDI_TIME_CODE: {
      int index       = msg.bytes[1] >> 4;
      int value       = msg.bytes[1] & 0x0F;
      bool freshFrame = index % 8 == 0;

      if (freshFrame) {
        target.frames++;
        if (target.frames >= target.numFrames) {
          target.frames %= target.numFrames;
          target.seconds++;
          if (target.seconds >= 60) {
            target.seconds %= 60;
            target.minutes++;
            if (target.minutes >= 60) {
              target.minutes %= 60;
              target.hours++;
            }
          }
        }
      }

      switch (index) {
        case 0x0: target.frames   = (target.frames  & 0xF0) | value; break;
        case 0x2: target.seconds  = (target.seconds & 0xF0) | value; break;
        case 0x4: target.minutes  = (target.minutes & 0xF0) | value; break;
        case 0x6: target.hours    = (target.hours   & 0xF0) | value; break;
        case 0x1: target.frames   = (target.frames  & 0x0F) | value << 4; break;
        case 0x3: target.seconds  = (target.seconds & 0x0F) | value << 4; break;
        case 0x5: target.minutes  = (target.minutes & 0x0F) | value << 4; break;
        case 0x7:
          target.hours = (target.hours & 0x0F) | value << 4;
          target.updateNumFrames();
          break;
        default: break;
      }
      break;
    }
    case MIDI_SYSEX:
      if (msg.bytes[0] == 0xf0 &&
          msg.bytes[1] == 0x7f &&
          msg.bytes[2] == 0x7f &&
          msg.bytes[3] == 0x01 &&
          msg.bytes[4] == 0x01 &&
          msg.bytes[9] == 0xf7)
      {
        target.hours    = msg.bytes[5];
        target.minutes  = msg.bytes[6];
        target.seconds  = msg.bytes[7];
        target.frames   = msg.bytes[8];
        target.updateNumFrames();
      }
    default: break;
  }
}
