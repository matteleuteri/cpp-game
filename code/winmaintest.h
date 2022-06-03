#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <stdint.h>
#include <profileapi.h>

#include "Scene.h"

static bool isRunning;
std::unique_ptr<Scene> scene;

// enum SCREENSTATE
// {
//     MAINMENU,
//     GAMING,
//     PAUSEMENU,
//     OTHER
// };
