#include "Scene.h"


Scene::Scene()
{
    player = new Player();// dont forget to free
}


void Scene::speedUp(DIRECTION direction)
{
    if(direction == LEFT)
    {
        (player->x)++; 
    }
}


void Scene::updateState()
{
    // update player position based on how long the key has been pressed down, or how long since releease it has been
}


void Scene::renderState(ID2D1HwndRenderTarget* pRT, RECT rc, ID2D1SolidColorBrush* pBlackBrush)
{
    pRT->BeginDraw();
    // clear to a black background
    pRT->Clear(D2D1::ColorF(D2D1::ColorF::Black));// "clears" the screen to a solid color

        // border of window
    pRT->DrawRectangle(D2D1::RectF(rc.left, rc.top, rc.right, rc.bottom), pBlackBrush);

        // border of playable area
    pRT->DrawRectangle(D2D1::RectF(rc.left + 100.0f, rc.top + 100.0f, rc.right - 100.0f, rc.bottom - 100.0f), pBlackBrush);
               
        // draw player
    pRT->DrawRectangle(D2D1::RectF(player->x, player->y, player->x + player->width, player->y + player->height), pBlackBrush);

    HRESULT hr = pRT->EndDraw();  
}

Scene::~Scene()
{
    delete player;
}