#include "Menu.h"


Menu::Menu(RECT *rc, HWND hwnd)
{}

void Menu::renderState(RECT* rc, HWND hwnd, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush* brushes[3], ID2D1Bitmap *button1Bitmap)
{
    renderTarget->BeginDraw();
    renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0,0));

    // draw black background
    renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

    // draw border of window
    D2D1_RECT_F border = D2D1::RectF((float)rc->left, (float)rc->top, (float)rc->right, (float)rc->bottom);
    renderTarget->DrawRectangle(border, brushes[0]);

    // renderGrid(rc, renderTarget, brushes);















    D2D1_SIZE_F size = button1Bitmap->GetSize();

    renderTarget->DrawBitmap(button1Bitmap, D2D1::RectF(
                100, 
                100, 
                500, 
                200));




    // returns HRESULT
    renderTarget->EndDraw();  
}