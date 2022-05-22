#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <stdint.h>
#include <profileapi.h>

#include "Scene.h"


static bool isRunning;
static win32_offscreen_buffer GlobalBackbuffer;
static Player* player;