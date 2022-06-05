#ifndef _MENU
#define _MENU

#include <windows.h>
#include <d2d1.h>
#include <stdint.h>


class Menu
{
public:
    bool isActive;
    Menu::Menu(RECT* rc, HWND hwnd);
    void Menu::renderState(RECT* rc, HWND hwnd, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush* brushes[3], ID2D1Bitmap *button1Bitmap);

};

#endif