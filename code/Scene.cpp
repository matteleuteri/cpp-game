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
        player->rightSpeed += 0.025;
        if(player->rightSpeed > 1.0)
        {
            player->rightSpeed = 1.0;
        }
    }
    else
    {
        player->moveTowardsZero(RIGHT);
    }

    if(player->goingLeft)
    {
        (player->leftSpeed) += 0.025;
        if(player->leftSpeed > 1.0)
        {
            player->leftSpeed = 1.0;
        }
    }
    else
    {
        player->moveTowardsZero(LEFT); 
    }

    if(player->goingDown)
    {
        (player->downSpeed) += 0.025;
        if(player->downSpeed > 1.0)
        {
            player->downSpeed = 1.0;
        }
    }
    else
    {
        player->moveTowardsZero(DOWN);
    }

    if(player->goingUp)
    {
        (player->upSpeed) += 0.025;
        if(player->upSpeed > 1.0)
        {
            player->upSpeed = 1.0;
        }
    }
    else
    {
        player->moveTowardsZero(UP);
    }


    // BUG: adding to x and y is delayed, subtracting is not.
    player->x += (player->rightSpeed* (timeElapsed / 50000));
    player->x -= (player->leftSpeed * (timeElapsed / 50000));

    player->y += (player->downSpeed * (timeElapsed / 50000));
    player->y -= (player->upSpeed * (timeElapsed / 50000));

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

void Scene::renderState(RECT* rc, ID2D1HwndRenderTarget* renderTarget)
{
    renderTarget->BeginDraw();
    // clear to a black background
    renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));// "clears" the screen to a solid color

    // border of window
    renderTarget->DrawRectangle(D2D1::RectF(rc->left, rc->top, rc->right, rc->bottom), brushes[0]);

    // border of playable area
    renderTarget->DrawRectangle(D2D1::RectF(rc->left + 100.0f, rc->top + 100.0f, rc->right - 100.0f, rc->bottom - 100.0f), brushes[0]);
               
    // draw player
    renderTarget->FillRectangle(D2D1::RectF(player->x, player->y, player->x + player->width, player->y + player->height), brushes[0]);

    HRESULT hr = renderTarget->EndDraw();  
}



ID2D1HwndRenderTarget* Scene::createResources(HWND hwnd, RECT* rc)
{
    ID2D1Factory* pD2DFactory = NULL; // only needed here for initialization
    ID2D1HwndRenderTarget* renderTarget = NULL; // one of these is used by the main window

    // both return HRESULTs
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
    pD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rc->right - rc->left, rc->bottom - rc->top)), &renderTarget);
    

    for(int i = 0; i < sizeof(brushes) / sizeof(brushes[0]); i++)
    {
        renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Pink), &brushes[i]); 
    }

    return renderTarget;
}