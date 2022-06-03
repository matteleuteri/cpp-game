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
// std::unique_ptr<Menu> menu;







HRESULT LoadBitmapFromFile(IWICImagingFactory *pIWICFactory, PCWSTR uri, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap **ppBitmap);



ID2D1HwndRenderTarget* renderTarget;
ID2D1SolidColorBrush* brushes[3];
void createResources(HWND hwnd, RECT* rc);
ID2D1Bitmap *playerBitmap;
ID2D1Bitmap *enemyBitmap;



// enum SCREENSTATE
// {
//     MAINMENU,
//     GAMING,
//     PAUSEMENU,
//     OTHER
// };
