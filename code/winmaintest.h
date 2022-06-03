#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <stdint.h>
#include <profileapi.h>

#include "Scene.h"
#include "Menu.h"

static bool isRunning;
std::unique_ptr<Scene> scene;
std::unique_ptr<Menu> menu;

// enum SCREENSTATE
// {
//     MAINMENU,
//     GAMING,
//     PAUSEMENU,
//     OTHER
// };
