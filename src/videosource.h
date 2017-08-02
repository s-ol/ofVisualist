#pragma once

#include "ofMain.h"

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
