#include "Scene.h"


Scene::Scene()
{
    projectiles = {};
    player = new Player();// dont forget to free
}
Scene::~Scene()
{
    delete player;
}



void Scene::updateProjectiles(int64_t timeElapsed)
{
    for(Projectile* proj : projectiles)
    {
        proj->x += (proj->direction[0]*10);
        proj->y += (proj->direction[1]*10);
        if(proj->y <= 0 || proj->y >= 720 || proj->x <= 0 || proj->x >= 1280)
        {
            // delete proj;
            proj->isActive = false;
        }
    }
}

void Scene::updateState(int64_t timeElapsed)
{
    player->updatePlayer(timeElapsed);
    updateProjectiles(timeElapsed);
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

    for(Projectile* p : projectiles)
    {
        // OutputDebugString("here\n"); 
        renderTarget->FillRectangle(D2D1::RectF(p->x, p->y, p->x + 10, p->y+10), brushes[0]);        
    }

    HRESULT hr = renderTarget->EndDraw();  
}



ID2D1HwndRenderTarget* Scene::createResources(HWND hwnd, RECT* rc)
{
    ID2D1Factory* pD2DFactory = NULL; // only needed here for initialization
    ID2D1HwndRenderTarget* renderTarget = NULL; // one of these is used by the main window

    // both lines below return HRESULT, I should make sure they succeez
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
    pD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rc->right - rc->left, rc->bottom - rc->top)), &renderTarget);
    
    // for(int i = 0; i < sizeof(brushes) / sizeof(brushes[0]); i++) // do this better
    // {
        renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &brushes[0]); 
        renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &brushes[1]); 
        renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Pink), &brushes[2]); 
    // }

    return renderTarget;
}