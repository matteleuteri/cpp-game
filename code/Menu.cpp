#include "Menu.h"

// Menu::Menu(RECT* rc, HWND hwnd)
// { 
// }
// Menu::~Menu()
// {
// }
// void Menu::renderState(RECT* rc, HWND hwnd)
// {



//     renderTarget->BeginDraw();
//     // renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0,0));

//     // // draw black background
//     // renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

//     // // draw border of window

//     // D2D1_RECT_F border = D2D1::RectF((float)rc->left, (float)rc->top, (float)rc->right, (float)rc->bottom);



//     // renderTarget->DrawRectangle(border, brushes[0]);

//     renderTarget->EndDraw();  

// }
// void Menu::updateState(int64_t startTime, int64_t endTime)
// {
// }
// void Menu::createResources(HWND hwnd, RECT* rc)
// {
//     ID2D1Factory* pD2DFactory = NULL;
//     D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
//     D2D1_SIZE_U clientSize = D2D1::SizeU(rc->right - rc->left, rc->bottom - rc->top);
//     pD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hwnd, clientSize), &renderTarget);
  
//     renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &brushes[0]); 
//     renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &brushes[1]); 
//     renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Pink), &brushes[2]); 
// }