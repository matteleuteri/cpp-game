#ifndef _SCENE
#define _SCENE

#include <windows.h>
#include <stdint.h>
#include <math.h>
#include <d2d1.h>

#include "Player.h"


class Scene
{
public:
    ID2D1SolidColorBrush* brushes[3];
    Player* player;

    Scene::Scene();
    Scene::~Scene();
    
    void Scene::updatePlayer(int64_t timeElapsed);
    void Scene::renderState(RECT* rc, ID2D1HwndRenderTarget* renderTarget);
    /*static*/ ID2D1HwndRenderTarget* Scene::createResources(HWND hwnd, RECT* rc);
};

#endif