#include "Scene.h"


Scene::Scene(HWND hwnd, RECT* rc)
{
    projectiles = {};
    player = new Player();// dont forget to free
    renderTarget = createResources(hwnd, rc);
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


void Scene::renderState(RECT* rc)
{
    renderTarget->BeginDraw();
    renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0,0));

    // draw black background
    renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

    // draw border of window
    renderTarget->DrawRectangle(D2D1::RectF(rc->left, rc->top, rc->right, rc->bottom), brushes[0]);

    // darw border of playable area
    renderTarget->DrawRectangle(D2D1::RectF(rc->left + 100.0f, rc->top + 100.0f, rc->right - 100.0f, rc->bottom - 100.0f), brushes[1]);
               
    // draw player
    // renderTarget->FillRectangle(D2D1::RectF(player->x, player->y, player->x + player->width, player->y + player->height), brushes[2]);

    // draw projectiles
    for(Projectile* p : projectiles)
    {
        renderTarget->FillRectangle(D2D1::RectF(p->x, p->y, p->x + 10, p->y+10), brushes[0]);        
    }
    
    renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(player->x, player->y));
    renderTarget->FillGeometry(playerGeometry, brushes[0]);
    
    HRESULT hr = renderTarget->EndDraw();  
}



ID2D1HwndRenderTarget* Scene::createResources(HWND hwnd, RECT* rc)
{
    ID2D1Factory* pD2DFactory = NULL;
    ID2D1HwndRenderTarget* renderTarget = NULL;

    // both lines below return HRESULT, I should make sure they succeez
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
    pD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rc->right - rc->left, rc->bottom - rc->top)), &renderTarget);
  
    renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &brushes[0]); 
    renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &brushes[1]); 
    renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Pink), &brushes[2]); 

    
    // player's geomery is defined here for now 
    pD2DFactory->CreatePathGeometry(&playerGeometry); // is this the right parameter
    ID2D1GeometrySink *pSink = NULL;
    playerGeometry->Open(&pSink);

    pSink->SetFillMode(D2D1_FILL_MODE_WINDING);
    pSink->BeginFigure(D2D1::Point2F(0,0), D2D1_FIGURE_BEGIN_FILLED);
    D2D1_POINT_2F points[6] = 
    {
        D2D1::Point2F(-10, -10),
        D2D1::Point2F(0, -7.5),
        D2D1::Point2F(10, -10),
        D2D1::Point2F(10, 10),
        D2D1::Point2F(-10, 10), 
        D2D1::Point2F(-10, -10),
    };
    pSink->AddLines(points, ARRAYSIZE(points));
    pSink->EndFigure(D2D1_FIGURE_END_CLOSED);

    pSink->Close();

    return renderTarget;
}