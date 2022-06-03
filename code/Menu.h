#ifndef _MENU
#define _MENU

#include <windows.h>
#include <d2d1.h>
#include <stdint.h>


class Menu
{
public:
    float x;
    float y;
    bool isActive;

    // ID2D1SolidColorBrush* brushes[3];
    // ID2D1HwndRenderTarget* renderTarget;

    // Menu::Menu(RECT* rc, HWND hwnd);
    // Menu::~Menu();
    // void Menu::createResources(HWND hwnd, RECT* rc);

    // void Menu::renderState(RECT* rc, HWND hwnd);
    // void Menu::updateState(int64_t startTime, int64_t endTime);

};

#endif