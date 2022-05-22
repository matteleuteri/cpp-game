#include "Scene.h"
// todo organize to iterate first over pen, then over corresponding shapes associated with the pens (players)

void renderScene(HWND hwnd, Player* player) 
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    // gets bounds of current client rectangle, which may be larger or smaller than play area
    RECT rc;
    GetClientRect(hwnd, &rc);
    HRGN bgRgn = CreateRectRgnIndirect(&rc);
    
    // declare tools
    HBRUSH blackBrush = CreateSolidBrush(RGB(0,0,0));
    HPEN hPen = CreatePen(PS_SOLID, 10, RGB(255,0,0));
    // select tools
    SelectObject(hdc, hPen);
    SelectObject(hdc, blackBrush);






    // use tools
    FillRgn(hdc, bgRgn, blackBrush); // background
    Rectangle(hdc, 100, 100, 1200, 600); // play area border
    
    // paint players here
    if(player)
    {
        Rectangle(hdc, player->x, player->y, player->x + player->width, player->y + player->height);
    }





    // free tools
    DeleteObject(hPen);
    DeleteObject(blackBrush);

    EndPaint(hwnd, &ps);
}
