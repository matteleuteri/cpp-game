#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <stdint.h>
#include <profileapi.h>
#include <filesystem>

#include "Scene.h"
#include "Menu.h"
#include "ButtonAction.h"
#include "FireButton.h"

enum SCREENSTATE
{
    MAINMENU,
    SCENE,
    PAUSEMENU
};

std::filesystem::path p;
static bool isRunning;
std::unique_ptr<Scene> scene;
std::unique_ptr<Menu> menu;
ID2D1HwndRenderTarget* renderTarget;
ID2D1SolidColorBrush* brushes[3];
SCREENSTATE screenState;

ID2D1Bitmap *playerBitmap;
ID2D1Bitmap *enemyBitmap;
ID2D1Bitmap *button1Bitmap;// use a better name
ID2D1Bitmap *projectile1Bitmap;
ID2D1Bitmap *targetBitmap;
ID2D1Bitmap *explosion1Bitmap;
ID2D1Bitmap *explosion2Bitmap;
ID2D1Bitmap *explosion3Bitmap;

// button 
ButtonAction *q_Button;
ButtonAction *w_Button;
ButtonAction *e_Button;
ButtonAction *r_Button;
