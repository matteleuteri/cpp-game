#include "Scene.h"

// todo organize to iterate first over pen, then over corresponding shapes associated with the pens (players)
void renderScene(HWND hwnd) 
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    // only shape to render is one rectangle
    RECT rc;
    GetClientRect(hwnd, &rc);
    
    // figure out what these two lines do????
    HGDIOBJ original = NULL;
    original = SelectObject(ps.hdc, GetStockObject(DC_PEN));
    
    HPEN blackPen = CreatePen(PS_SOLID, 3, 0);
    
    SelectObject(ps.hdc, blackPen);

    // only being done once for now
    drawShape(&ps, &rc);

    DeleteObject(blackPen);

    EndPaint(hwnd, &ps);
}

void drawShape(PAINTSTRUCT *ps, RECT *rc) 
{
    Rectangle(ps->hdc, rc->left + 100, rc->top + 100, rc->right - 100, rc->bottom - 100);
}