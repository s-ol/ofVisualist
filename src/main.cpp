#include "ofMain.h"
#include "effectApp.h"
#include "uiApp.h"

int main(int argc, const char** argv) {
  shared_ptr<EffectApp> effect = nullptr;
  if (argc == 3) {
    ofGLWindowSettings outputSettings;
    outputSettings.setGLVersion(3, 0);
    outputSettings.width = atoi(argv[1]);
    outputSettings.height = atoi(argv[2]);
    outputSettings.windowMode = OF_FULLSCREEN;
    ofLogNotice() << outputSettings.width << "x" << outputSettings.height;
    auto outputWindow = ofCreateWindow(outputSettings);
    effect = make_shared<EffectApp>();
    ofRunApp(outputWindow, effect);
  }

  ofGLWindowSettings uiSettings;
  uiSettings.setGLVersion(3, 0);
  uiSettings.width = 400;
  uiSettings.height = 800;
  uiSettings.windowMode = OF_WINDOW;
  auto uiWindow = ofCreateWindow(uiSettings);
  auto ui = make_shared<UiApp>(effect);
  ofRunApp(uiWindow, ui);
  ofRunMainLoop();
}
