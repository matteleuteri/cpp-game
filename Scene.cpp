#include "Scene.h"
// todo organize to iterate first over pen, then over corresponding shapes associated with the pens (players)
void renderScene(HWND hwnd) 
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    RECT rc;
    GetClientRect(hwnd, &rc);

    // fill background region
    HRGN bgRgn = CreateRectRgnIndirect(&rc);
    

    HBRUSH backgroundBrush = CreateSolidBrush(RGB(0,0,0));
    HPEN hPen = CreatePen(PS_SOLID,10,RGB(255,0,0));
    
    SelectObject(hdc, hPen);
    SelectObject(hdc, backgroundBrush);


    FillRgn(hdc, bgRgn, backgroundBrush);

    Rectangle(hdc, 100,100,800,600);

    // Rectangle(hdc, xPos, yPos,xPos + 20,yPos + 20);
    

    DeleteObject(hPen);
    DeleteObject(backgroundBrush);

    EndPaint(hwnd, &ps);
}

void paintBackground(PAINTSTRUCT *ps, RECT *rc) 
{
    Rectangle(ps->hdc, rc->left, rc->top, rc->right, rc->bottom);  
}


void drawRectangle(PAINTSTRUCT *ps, RECT *rc) 
{
    //Rectangle(ps->hdc, rc->left, rc->top, rc->right, rc->bottom);
    Rectangle(ps->hdc, 100, 100, 600, 400);
}



















void renderScene2(HWND hwnd, POINT pt) 
{

    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    RECT rc;
    GetClientRect(hwnd, &rc);

    // fill background region
    HRGN bgRgn = CreateRectRgnIndirect(&rc);
    

    HBRUSH backgroundBrush = CreateSolidBrush(RGB(0,0,0));
    HPEN hPen = CreatePen(PS_SOLID,10,RGB(255,0,0));
    
    SelectObject(hdc, hPen);
    SelectObject(hdc, backgroundBrush);



    Rectangle(hdc, pt.x, pt.y, pt.x+20, pt.y+20);

    // Rectangle(hdc, xPos, yPos,xPos + 20,yPos + 20);
    

    DeleteObject(hPen);
    DeleteObject(backgroundBrush);

    EndPaint(hwnd, &ps);


}