#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {
  ofLogNotice() << "isProg: " << ofIsGLProgrammableRenderer();
  ofGLFWWindowSettings settings;
  settings.setGLVersion(3, 0);
  settings.width = 1920;
  settings.height = 1080;

#ifdef _DEBUG
  settings.windowMode = OF_WINDOW;
#else
  settings.windowMode = OF_FULLSCREEN;;
#endif
  ofCreateWindow(settings);

  ofRunApp( new ofApp());
}
