#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {
#ifdef _DEBUG
  ofSetupOpenGL(SCREEN_RES, OF_WINDOW);
#else
  ofSetupOpenGL(SCREEN_RES, OF_FULLSCREEN);
#endif
  ofRunApp( new ofApp());
}
