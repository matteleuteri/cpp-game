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
    Player* player;
    Scene::Scene();
    Scene::~Scene();
    void Scene::speedUp(DIRECTION direction);
    void Scene::slowDown(DIRECTION direction);
    void Scene::updateState(int64_t timeElapsed);
    void Scene::renderState(ID2D1HwndRenderTarget* pRT, RECT rc, ID2D1SolidColorBrush* pBlackBrush);
};


#endif