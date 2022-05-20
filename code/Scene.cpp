#include "Scene.h"
// todo organize to iterate first over pen, then over corresponding shapes associated with the pens (players)
void renderScene(HWND hwnd) 
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    // gets bounds of current client rectangle, which may be larger or smaller than play area
    RECT rc;
    GetClientRect(hwnd, &rc);
    HRGN bgRgn = CreateRectRgnIndirect(&rc);
    
    // declare tools
    HBRUSH blackBrush = CreateSolidBrush(RGB(0,0,0));
    HPEN hPen = CreatePen(PS_SOLID,10,RGB(255,0,0));
    // select tools
    SelectObject(hdc, hPen);
    SelectObject(hdc, blackBrush);





    // use tools
    FillRgn(hdc, bgRgn, blackBrush); // background
    Rectangle(hdc, rc.left+100,rc.top+100,rc.right-100,rc.bottom-100); // play area border


    // paint players here






    // free tools ???
    DeleteObject(hPen);
    DeleteObject(blackBrush);

    EndPaint(hwnd, &ps);
}


