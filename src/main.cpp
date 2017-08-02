#include "ofMain.h"
#include "effectApp.h"
#include "uiApp.h"

int main(int argc, const char** argv) {
  shared_ptr<EffectApp> effect = nullptr;
  shared_ptr<ofAppBaseWindow> outputWindow = nullptr;
  if (false && argc == 3) {
    ofGLWindowSettings outputSettings;
    outputSettings.setGLVersion(3, 0);
    outputSettings.width = 1920;
    outputSettings.height = 1080;
    outputSettings.windowMode = OF_WINDOW;
    outputWindow = ofCreateWindow(outputSettings);
    effect = make_shared<EffectApp>();
    ofRunApp(outputWindow, effect);
  }

  ofGLWindowSettings uiSettings;
  uiSettings.setGLVersion(3, 0);
  uiSettings.width = 620;
  uiSettings.height = 300;
  uiSettings.windowMode = OF_WINDOW;
  auto uiWindow = ofCreateWindow(uiSettings);
  auto ui = make_shared<UiApp>(); //effect);
  ofRunApp(uiWindow, ui);
  ofRunMainLoop();
}
