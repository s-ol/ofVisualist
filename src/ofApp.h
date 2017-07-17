#pragma once

#include "ofMain.h"

#define COLOR_STEPS 8

class ofApp : public ofBaseApp{

  public:

    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);		

    ofVideoPlayer       fingerMovie;
    bool                frameByframe;
    float               speed = 100.0f;
    float               offset;
    ofColor             colors[COLOR_STEPS]; /* = {
       0x6C698D,
       0xB8D8BA,
       0xFF99C8,
       0xA0D2DB,
       0xE0D8DE,
       0xFE654F,
       0xFED18C,
       0xD6EFFF,
       0xFFEDB5,
     }; */
};

