#ifndef _SCENE
#define _SCENE

#include <windows.h>
#include <stdint.h>
#include <d2d1.h>
#include <vector>

#include "Player.h"
#include "Projectile.h"
#include <wincodec.h>
#include <combaseapi.h>
#include <Objbase.h>
class Scene
{
public:
    ID2D1SolidColorBrush* brushes[3];
    Player* player;
    std::vector<Projectile*> projectiles;
    ID2D1HwndRenderTarget* renderTarget;

    ID2D1Bitmap *playerBitmap;
    ID2D1Bitmap *enemyBitmap;

    Scene::Scene(HWND hwnd, RECT* rc);
    Scene::~Scene();
    void Scene::updateState(int64_t timeElapsed);
    void Scene::updateProjectiles(int64_t timeElapsed);
    void Scene::renderState(RECT* rc, HWND hwnd);
    void Scene::createResources(HWND hwnd, RECT* rc);
    HRESULT Scene::LoadBitmapFromFile(IWICImagingFactory *pIWICFactory, PCWSTR uri, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap **ppBitmap);

};

#endif