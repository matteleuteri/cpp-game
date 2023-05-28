#include "headers/Scene.h"

Scene::Scene(int64_t currentTime, bool ia, std::array<ID2D1Bitmap*, 12> bitmaps) : isActive(ia)
{
    player       = std::make_unique<Player>(bitmaps[1], 400.0f, 400.0f);
    animator     = std::make_unique<Animator>(currentTime, 0, 0, bitmaps);
    target       = std::make_unique<Target>(600, 600, bitmaps[2]);
    enemyManager = std::make_unique<EnemyManager>(currentTime, bitmaps[0]);
}

void Scene::updateProjectiles(int64_t timeElapsed)
{
    for(Projectile &proj : projectiles)
    {
        proj.x += (proj.direction[0] * timeElapsed / 10000);
        proj.y += (proj.direction[1] * timeElapsed / 10000);
        // leak memory (fix this!)
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
        player->update(timeElapsed, hwnd);
        // projectile update is handled by Scene

        animator->mountain->update(player.get(), timeElapsed);
        animator->mountain2->update(player.get(), timeElapsed);

        updateProjectiles(timeElapsed);

        if(enemyManager->isActive)
        {
            if(endTime - enemyManager->lastSpawnTime >= 20000000) enemyManager->spawnEnemy(endTime);

            for(int i = 0; i < sizeof(enemyManager->enemyList) / sizeof(Enemy*); i++)
            {
                Enemy* enemy = enemyManager->enemyList[i];
                if(enemy->isActive)
                {
                    enemy->update(projectiles, player.get(), animator.get(), timeElapsed, endTime);
                }   
            }
        }
        target->update(animator.get(), endTime);
        animator->refreshAnimationFrame(endTime);
    }
}

void Scene::renderState(RECT* rc, HWND hwnd, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush* brushes[3], IDWriteTextFormat* pTextFormat_)
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
        drawMountains(renderTarget);
        drawPlayer(renderTarget);
        drawProjectiles(renderTarget);
        drawTarget(renderTarget);
        drawExplosions(renderTarget);
        // can conditional draws be combined with others to be done in one call?
        if(enemyManager->isActive) 
        {
            for(Enemy* e: enemyManager->enemyList)
            {
                if(e->isActive) e->draw(renderTarget, player.get());
            }
        }

        if(animator->score->isActive) 
        {
            drawScore(renderTarget);
        }

        D2D1_RECT_F layoutRect = D2D1::RectF(
            static_cast<FLOAT>(rc->left),
            static_cast<FLOAT>(rc->top),
            static_cast<FLOAT>(rc->right - rc->left),
            static_cast<FLOAT>(rc->bottom - rc->top)
        );

        const wchar_t* wszText_ = L"This is my text, it has a null terminating charcetr\n";
        UINT32 cTextLength_ = 53;// check for overflow

        renderTarget->DrawText(
            wszText_,        // The string to render.
            cTextLength_,    // The string's length.
            pTextFormat_,    // The text format.
            layoutRect,       // The region of the window where the text will be rendered.
            brushes[0]);
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

void Scene::drawScore(ID2D1HwndRenderTarget* renderTarget)
{
    D2D1_POINT_2F center = {};
    center.x = 200.0f;
    center.y = 200.0f;        
    D2D1_SIZE_F size = animator->score->bitmap->GetSize();
                renderTarget->DrawBitmap(animator->score->bitmap, D2D1::RectF(
                animator->score->x - (size.width / 2), 
                animator->score->y - (size.height / 2), 
                animator->score->x + (size.width / 2), 
                animator->score->y + (size.height / 2)));
}

void Scene::drawMountains(ID2D1HwndRenderTarget* renderTarget)
{
    D2D1_SIZE_F size = animator->mountain->bitmap->GetSize();
    renderTarget->DrawBitmap(animator->mountain->bitmap, D2D1::RectF(
                animator->mountain->x - (size.width / 2), 
                animator->mountain->y - (size.height / 2), 
                animator->mountain->x + (size.width / 2), 
                animator->mountain->y + (size.height / 2)));
    
    size = animator->mountain2->bitmap->GetSize();
    renderTarget->DrawBitmap(animator->mountain2->bitmap, D2D1::RectF(
                animator->mountain2->x - (size.width / 2), 
                animator->mountain2->y - (size.height / 2), 
                animator->mountain2->x + (size.width / 2), 
                animator->mountain2->y + (size.height / 2)));
}


// void Scene::drawBM(GameObject* g)
// {
//     size = g->bitmap->GetSize();
//     renderTmrget->DrawBitmap(g->>bitmap, D2D1::RectF(
//                 g->x - (size.width / 2), 
//                 g->y - (size.height / 2), 
//                 g->x + (size.width / 2), 
//                 g->y + (size.height / 2)));
// }


