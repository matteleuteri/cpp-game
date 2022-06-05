#include "headers/Scene.h"


Scene::Scene(RECT* rc, HWND hwnd)
{
    projectiles = {};
    enemyManager = std::make_unique<EnemyManager>();
    enemyManager->lastSpawnTime = 0;
    player = std::make_unique<Player>();
}

Scene::~Scene() {}

void Scene::updateProjectiles(int64_t timeElapsed)
{
    for(Projectile &proj : projectiles)
    {
        proj.x += (proj.direction[0] * 10);
        proj.y += (proj.direction[1] * 10);
        // if(proj.y <= 0 || proj.y >= 720 || proj.x <= 0 || proj.x >= 1280)
        // {
        //     // delete projectile;
        //     timeElapsed *= 1;
        //     proj.isActive = false;
        // }
    }
}

void Scene::updateState(int64_t endTime, int64_t startTime)
{
    int64_t timeElapsed = endTime - startTime;

    if(player->isActive)
    {
        player->updatePlayer(timeElapsed);
        updateProjectiles(timeElapsed);

        if(endTime - enemyManager->lastSpawnTime >= 20000000)
        {
            OutputDebugStringA("Enemy spwaned.\n");
            enemyManager->spawnEnemy(endTime);
        }

        for(int i = 0; i < sizeof(enemyManager->enemyList) / sizeof(Enemy*); i++)
        {
            Enemy* enemy = enemyManager->enemyList[i];
            if(enemy != nullptr && enemy->isActive) // danger!
            {
                enemy->update(projectiles, player.get(), timeElapsed);
            }
        }
    }
}

void Scene::renderState(RECT* rc, HWND hwnd, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush* brushes[3])
{
    renderTarget->BeginDraw();
    renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0,0));

    // draw black background
    renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

    // draw border of window
    D2D1_RECT_F border = D2D1::RectF((float)rc->left, (float)rc->top, (float)rc->right, (float)rc->bottom);
    renderTarget->DrawRectangle(border, brushes[0]);

    renderGrid(rc, renderTarget, brushes);

    if(player->isActive) 
    {
        // float angle = 0; //  make property of player
        POINT mousePosition;
        BOOL cursorFound = GetCursorPos(&mousePosition);
        BOOL converted = ScreenToClient(hwnd, &mousePosition);

        if(cursorFound && converted)
        {
            player->pointPlayerTowards(mousePosition);
        }

        D2D1_POINT_2F center = {};
        center.x = player->x;
        center.y = player->y;

        D2D1_SIZE_F size = player->bitmap->GetSize();
        renderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(player->angle, center));

        renderTarget->DrawBitmap(player->bitmap, D2D1::RectF(
                    player->x - (size.width / 2), 
                    player->y - (size.height / 2), 
                    player->x + (size.width / 2), 
                    player->y + (size.height / 2)));

        renderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(0, center));

        // draw projectiles as rectabngels
        for(Projectile &p : projectiles)
        {
            renderTarget->FillRectangle(D2D1::RectF(p.x, p.y, p.x + 10, p.y + 10), brushes[0]);        
        }
        // draw enemies as bitmaps

        drawEnemies(renderTarget);
    }
    
    // HRESULT hr = renderTarget->EndDraw();  
    renderTarget->EndDraw();  
}


void Scene::renderGrid(RECT* rc, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush* brushes[3])
{
    // draw grid lines:
    for(int i = 0; i < rc->right; i++)
    {
        if(i % 32 == 0) 
        {
            renderTarget->DrawLine(D2D1::Point2F((float)i, 0.0f), D2D1::Point2F((float)i, (float)rc->bottom), brushes[0], 0.5f);
            renderTarget->DrawLine(D2D1::Point2F(0.0f, (float)i), D2D1::Point2F((float)rc->right, (float)i), brushes[0], 0.5f);
        }
    }
}

void Scene::drawEnemies(ID2D1HwndRenderTarget* renderTarget)
{
    for(Enemy *e : enemyManager->enemyList)
    {
        if(e == nullptr)
            return;

        if(!e->isActive)
            continue;

        float xDistance = (player->x) - (e->x);
        float yDistance = (player->y) - (e->y);

        e->angle = ((float)atan(yDistance / xDistance) * (180.0f /PI)) + 45.0f;

        if(player->x < e->x) e->angle += 180; // not sure why, but this is important

        D2D1_POINT_2F center = {};
        center.x = e->x;
        center.y = e->y;

        renderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(e->angle, center));

        D2D1_SIZE_F enemy_size = e->bitmap->GetSize();
        renderTarget->DrawBitmap(e->bitmap, D2D1::RectF(
                    e->x - (enemy_size.width / 2), 
                    e->y - (enemy_size.height / 2), 
                    e->x + (enemy_size.width / 2), 
                    e->y + (enemy_size.height / 2)));
    
        renderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(0, center));
    }
}