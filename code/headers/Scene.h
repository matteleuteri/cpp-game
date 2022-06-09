#ifndef _SCENE
#define _SCENE

#define PI 3.141592653589793238463f

#include <windows.h>
#include <stdint.h>
#include <d2d1.h>
#include <vector>
#include <memory>
#include <wincodec.h>
#include <combaseapi.h>
#include <Objbase.h>

#include "Player.h"
#include "Projectile.h"
#include "EnemyManager.h"
#include "Animator.h"
#include "Target.h"

class Scene
{
public:
    std::vector<Projectile> projectiles;

    std::unique_ptr<Player> player;
    std::unique_ptr<EnemyManager> enemyManager;
    std::unique_ptr<Animator> animator;
    std::unique_ptr<Target> target;

    bool isActive;

    Scene::Scene(RECT* rc, HWND hwnd);

    //drawing
    void Scene::drawExplosions(ID2D1HwndRenderTarget* renderTarget);
    void Scene::drawPlayer(ID2D1HwndRenderTarget* renderTarget);
    void Scene::drawProjectiles(ID2D1HwndRenderTarget* renderTarget);
    void Scene::drawTarget(ID2D1HwndRenderTarget* renderTarget);
    void Scene::drawEnemies(ID2D1HwndRenderTarget* renderTarget);
    void Scene::assignBitmaps(ID2D1Bitmap *playerBitmap, ID2D1Bitmap *enemyBitmap, ID2D1Bitmap *targetBitmap, ID2D1Bitmap *explosion1Bitmap,ID2D1Bitmap *explosion2Bitmap,ID2D1Bitmap *explosion3Bitmap);
    void Scene::renderState(RECT* rc, HWND hwnd, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush* brushes[3]);
    void Scene::renderGrid(RECT* rc, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush* brushes[3]);
    
    void Scene::updateState(HWND hwnd, int64_t startTime, int64_t endTime); 
    void Scene::updateProjectiles(int64_t timeElapsed);
    
};

#endif