#include "Scene.h"


Scene::Scene()
{
    player = new Player();// dont forget to free
}


void Scene::speedUp(DIRECTION direction)
{

    if(direction == RIGHT)
    {
        player->goingRight = true; 
    }
    else if(direction == LEFT)
    {
        player->goingLeft = true;
    }
    else if(direction == UP)
    {
        player->goingUp = true;    
    }
    else if(direction == DOWN)
    {
        player->goingDown = true;
    }
}

void Scene::slowDown(DIRECTION direction)
{
    if(direction == RIGHT)
    {
        player->goingRight = false; 
    }
    else if(direction == LEFT)
    {
        player->goingLeft = false;
    }
    else if(direction == UP)
    {
        player->goingUp = false;    
    }
    else if(direction == DOWN)
    {
        player->goingDown = false;
    }
}

void Scene::updateState(int64_t timeElapsed)
{
    if(player->goingRight)
    {
        (player->xSpeed) += 0.01;
        if(player->xSpeed > 1.0)
        {
            player->xSpeed = 1.0;
            player->goingRight = false;
        }
    }
    if(player->goingLeft)
    {
        (player->xSpeed) -= 0.01;
        if(player->xSpeed < -1.0)
        {
            player->xSpeed = -1.0;
            player->goingLeft = false;
        }
    }
    if(player->goingUp)
    {
        (player->ySpeed) -= 0.01;
        if(player->ySpeed < -1.0)
        {
            player->ySpeed = -1.0;
            player->goingUp = false;
        }
    }
    if(player->goingDown)
    {
        (player->ySpeed) += 0.01;
        if(player->ySpeed > 1.0)
        {
            player->ySpeed = 1.0;
            player->goingDown = false;
        }
    }

    player->x += (player->xSpeed * (timeElapsed / 10000000));
    player->y += (player->ySpeed * (timeElapsed / 10000000));

    if(player->x > 1280)
    {
        player->x = 0;
    }
    else if(player->x < 0)
    {
        player->x = 1280;
    }

    if(player->y > 720)
    {
        player->y = 0;
    }
    else if(player->y < 0)
    {
        player->y = 720;
    }

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