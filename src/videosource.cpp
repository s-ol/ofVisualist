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
