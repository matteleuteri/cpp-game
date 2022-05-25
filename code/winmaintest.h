#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <stdint.h>
#include <profileapi.h>

#include "Scene.h"


static bool isRunning;
static game_offscreen_buffer GlobalBackbuffer;
static Player* player;

enum SCREENSTATE
{
    MAINMENU,
    GAMING,
    PAUSEMENU,
    OTHER
};


struct windowConfigs 
{
    int width; 
    int height;
    SCREENSTATE screenState;
    // refresh rate??? what else???
};