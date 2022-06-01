#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <stdint.h>
#include <profileapi.h>

#include "Scene.h"


static bool isRunning;
static Player* player;
static Scene* scene;

// enum SCREENSTATE
// {
//     MAINMENU,
//     GAMING,
//     PAUSEMENU,
//     OTHER
// };
