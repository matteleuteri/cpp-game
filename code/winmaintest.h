#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <profileapi.h>
#include <stdint.h>
#include "Scene.h"

static bool isRunning;
static int FRAMES_PER_SECOND;
Player *player;

// struct StateInfo 
// {};

// inline StateInfo* GetAppState(HWND hwnd)
// {
//     LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
//     StateInfo *pState = reinterpret_cast<StateInfo*>(ptr);
//     return pState;
// }