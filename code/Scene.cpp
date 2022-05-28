#include "Scene.h"


Scene::Scene()
{
    player = new Player();// dont forget to free
}
Scene::~Scene()
{
    delete player;
}




void Scene::updatePlayer(int64_t timeElapsed)
{
    if(player->goingRight)
    {
        player->xSpeed += 0.05;
        if(player->xSpeed > 1)
        {
            player->xSpeed = 1.0;
        }
    }
    else if(!player->goingLeft)
    {
        player->moveTowardsZeroX();
    }

    if(player->goingLeft)
    {
        (player->xSpeed) -= 0.05;
        if(player->xSpeed < -1.0)
        {
            player->xSpeed = -1.0;
            // player->goingLeft = false;
        }
    }
    else if(!player->goingRight)
    {
        player->moveTowardsZeroX();  
    }

    if(player->goingDown)
    {
        (player->ySpeed) += 0.05;
        if(player->ySpeed > 1.0)
        {
            player->ySpeed = 1.0;
            // player->goingDown = false;
        }
    }
    else if(!player->goingUp)
    {
        player->moveTowardsZeroY();
    }

    if(player->goingUp)
    {
        (player->ySpeed) -= 0.05;
        if(player->ySpeed < -1.0)
        {
            player->ySpeed = -1.0;
            // player->goingUp = false;
        }
    }
    else if(!player->goingDown)
    {
        player->moveTowardsZeroY();
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

void Scene::renderState(RECT* rc, ID2D1HwndRenderTarget* pRT)
{
    pRT->BeginDraw();
    // clear to a black background
    pRT->Clear(D2D1::ColorF(D2D1::ColorF::Black));// "clears" the screen to a solid color

    // border of window
    pRT->DrawRectangle(D2D1::RectF(rc->left, rc->top, rc->right, rc->bottom), pPinkBrush);

    // border of playable area
    pRT->DrawRectangle(D2D1::RectF(rc->left + 100.0f, rc->top + 100.0f, rc->right - 100.0f, rc->bottom - 100.0f), pOrangeBrush);
               
    // draw player
    pRT->FillRectangle(D2D1::RectF(player->x, player->y, player->x + player->width, player->y + player->height), pPinkBrush);

    HRESULT hr = pRT->EndDraw();  
}



ID2D1HwndRenderTarget* Scene::createResources(HWND hwnd, RECT* rc)
{
    ID2D1Factory* pD2DFactory = NULL; // only needed here for initialization
    ID2D1HwndRenderTarget* pRT = NULL; // one of these is used by the main window
    pPinkBrush = NULL;
    pOrangeBrush = NULL;
    // pOrangeBrush = NULL;

    //  returns HRESULT
    if(!D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory))
    {
        // handle failure to create factory
    }

    pD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rc->right - rc->left, rc->bottom - rc->top)), &pRT);
    
    pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Pink), &pPinkBrush); 
    pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Orange), &pOrangeBrush); 

    return pRT;
}