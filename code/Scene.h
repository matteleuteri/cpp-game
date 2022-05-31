#ifndef _SCENE
#define _SCENE

#include <windows.h>
#include <stdint.h>
// #include <math.h>
#include <d2d1.h>
#include <vector>

#include "Player.h"
#include "Projectile.h"


class Scene
{
public:
    ID2D1SolidColorBrush* brushes[3];
    Player* player;
    std::vector<Projectile*> projectiles;

    Scene::Scene();
    Scene::~Scene();
    void Scene::updateState(int64_t timeElapsed);
    void Scene::updateProjectiles(int64_t timeElapsed);
    void Scene::renderState(RECT* rc, ID2D1HwndRenderTarget* renderTarget);
    ID2D1HwndRenderTarget* Scene::createResources(HWND hwnd, RECT* rc);
};

#endif