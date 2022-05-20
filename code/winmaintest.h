#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "Scene.h"

static bool isRunning;
static int FRAMES_PER_SECOND;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
