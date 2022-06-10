#include "headers/Scene.h"


Scene::Scene(RECT* rc, HWND hwnd)
{
    projectiles = {};
    player = std::make_unique<Player>();
    animator = std::make_unique<Animator>();
    target = std::make_unique<Target>();
    target->x = 600;
    target->y = 600;
    enemyManager = std::make_unique<EnemyManager>();
    enemyManager->lastSpawnTime = 0;
}

void Scene::updateProjectiles(int64_t timeElapsed)
{
    for(Projectile &proj : projectiles)
    {
        proj.x += (proj.direction[0] * timeElapsed / 10000);
        proj.y += (proj.direction[1] * timeElapsed / 10000);
        // if(proj.y <= 0 || proj.y >= 720 || proj.x <= 0 || proj.x >= 1280)
        // {
        //     // delete projectile;
        //     timeElapsed *= 1;
        //     proj.isActive = false;
        // }
    }
}

void Scene::updateState(HWND hwnd, int64_t endTime, int64_t startTime)
{
    int64_t timeElapsed = endTime - startTime;

    if(player->isActive)
    {
        // float angle = 0; //  make property of player
        POINT mousePosition;
        BOOL cursorFound = GetCursorPos(&mousePosition);
        BOOL converted = ScreenToClient(hwnd, &mousePosition);
        
        player->updatePlayer(timeElapsed);
        updateProjectiles(timeElapsed);

        animator->refreshAnimationFrame(endTime);

        if(cursorFound && converted)
        {
            player->pointPlayerTowards(mousePosition);
        }

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
                enemy->update(projectiles, player.get(), animator.get(), timeElapsed, endTime);
            }
        }
        target->checkIfHit(animator.get(), endTime);
    }
}

void Scene::renderState(RECT* rc, HWND hwnd, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush* brushes[3])
{
    renderTarget->BeginDraw();
    renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0,0));
    renderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(0,{0,0}));
    // draw black background
    renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
    // draw border of window
    D2D1_RECT_F border = D2D1::RectF((float)rc->left, (float)rc->top, (float)rc->right, (float)rc->bottom);
    renderTarget->DrawRectangle(border, brushes[0]);
    
    // mark last enemy hit
    renderGrid(rc, renderTarget, brushes);

    if(player->isActive) 
    {
        drawPlayer(renderTarget);
        drawEnemies(renderTarget);
        drawProjectiles(renderTarget);
        drawTarget(renderTarget);
        drawExplosions(renderTarget);
        if(animator->score->isActive)
        {
            drawScore(renderTarget);
        }
    }
    renderTarget->EndDraw();  
}

void Scene::drawExplosions(ID2D1HwndRenderTarget* renderTarget)
{
    for(auto& explosion: animator->explosions)
    {
        // draw explosion's current bitmap at its curretn transform
        D2D1_SIZE_F size = explosion.bitmap->GetSize();
        renderTarget->DrawBitmap(explosion.bitmap, D2D1::RectF(
                    explosion.x - (size.width / 2), 
                    explosion.y - (size.height / 2), 
                    explosion.x + (size.width / 2), 
                    explosion.y + (size.height / 2)));
    }
}

void Scene::drawTarget(ID2D1HwndRenderTarget* renderTarget)
{
    D2D1_SIZE_F size = target->bitmap->GetSize();
    renderTarget->DrawBitmap(target->bitmap, D2D1::RectF(
                target->x - (size.width / 2), 
                target->y - (size.height / 2), 
                target->x + (size.width / 2), 
                target->y + (size.height / 2)));
}

void Scene::renderGrid(RECT* rc, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush* brushes[3])
{
    renderTarget->DrawLine(D2D1::Point2F((float)animator->gridCol, 0.0f), 
                D2D1::Point2F((float)animator->gridCol, (float)rc->bottom), brushes[0], 0.75f);
    renderTarget->DrawLine(D2D1::Point2F(0.0f, (float)animator->gridRow), 
                D2D1::Point2F((float)rc->right, (float)animator->gridRow), brushes[0], 0.75f);
}

void Scene::drawEnemies(ID2D1HwndRenderTarget* renderTarget)
{
    // this is kind of a mess
    for(Enemy *e : enemyManager->enemyList)
    {
        if(e == nullptr)
            return;

        if(!e->isActive)
            continue;

        float xDistance = player->x - e->x;
        float yDistance = player->y - e->y;

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

void Scene::drawPlayer(ID2D1HwndRenderTarget* renderTarget)
{
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
}

void Scene::drawProjectiles(ID2D1HwndRenderTarget* renderTarget)
{
    for(Projectile &p : projectiles)
    {
        D2D1_POINT_2F center = {};
        center.x = p.x;
        center.y = p.y;        
        D2D1_SIZE_F size = p.bitmap->GetSize();
        renderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(p.angle, center));
        renderTarget->DrawBitmap(p.bitmap, D2D1::RectF(
                    p.x - (size.width / 2), 
                    p.y - (size.height / 2), 
                    p.x + (size.width / 2), 
                    p.y + (size.height / 2)));
        renderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(0, center));
    }
}

void Scene::assignBitmaps(ID2D1Bitmap *playerBitmap, ID2D1Bitmap *enemyBitmap, ID2D1Bitmap *targetBitmap,
            ID2D1Bitmap *explosion1Bitmap,ID2D1Bitmap *explosion2Bitmap,ID2D1Bitmap *explosion3Bitmap)
{
    enemyManager->bitmap = enemyBitmap;
    player->bitmap = playerBitmap;
    target->bitmap = targetBitmap;
    animator->explosionBitmaps[0] = explosion1Bitmap;
    animator->explosionBitmaps[1] = explosion2Bitmap;
    animator->explosionBitmaps[2] = explosion3Bitmap;
}

void Scene::assignBitmaps2(ID2D1Bitmap *one_01, ID2D1Bitmap *one_02, ID2D1Bitmap *one_03, ID2D1Bitmap *one_04)
{
    animator->scoreBitmaps[0] = one_01;
    animator->scoreBitmaps[1] = one_02;

    animator->scoreBitmaps[2] = one_03;

    animator->scoreBitmaps[3] = one_04;

}

void Scene::drawScore(ID2D1HwndRenderTarget* renderTarget)
{
    D2D1_POINT_2F center = {};
    center.x = 200.0f;
    center.y = 200.0f;        
    D2D1_SIZE_F size = animator->score->bitmap->GetSize();
    // renderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(p.angle, center));
        renderTarget->DrawBitmap(animator->score->bitmap, D2D1::RectF(
                    animator->score->x - (size.width / 2), 
                    animator->score->y - (size.height / 2), 
                    animator->score->x + (size.width / 2), 
                    animator->score->y + (size.height / 2)));
        // renderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(0, center));    
}
