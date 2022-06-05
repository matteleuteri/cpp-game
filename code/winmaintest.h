#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <stdint.h>
#include <profileapi.h>
// #include <memory>

#include "Scene.h"
#include "Menu.h"

static bool isRunning;
std::unique_ptr<Scene> scene;
std::unique_ptr<Menu> menu;
ID2D1HwndRenderTarget* renderTarget;
ID2D1SolidColorBrush* brushes[3];
ID2D1Bitmap *playerBitmap;
ID2D1Bitmap *enemyBitmap;

void createResources(HWND hwnd, RECT* rc);
HRESULT LoadBitmapFromFile(IWICImagingFactory *pIWICFactory, PCWSTR uri, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap **ppBitmap);


// enum SCREENSTATE
// {
//     MAINMENU,
//     GAMING,
//     PAUSEMENU,
//     OTHER
// };
