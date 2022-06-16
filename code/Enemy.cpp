#include "headers/Enemy.h"

// funcitons for enemy go here, like turn angle and reactionspeed
Enemy::Enemy() 
{
    isActive = true;
}

Enemy::Enemy(float x, float y, bool ia, ID2D1Bitmap* b) : x(x), y(y), isActive(ia), bitmap(b)
{}

void Enemy::move(Player* player, int64_t timeElapsed) // needs time elapsed as well
{
    //TODO
    // NOW the player moves using x and y distance at some offset in either direction
    // LATER the player moves using an angle at some offset
    // float d = (float)tan(angle * 3.14159265358979323 / 180);

    float xDist = player->x - x;
    float yDist = player->y - y;

    x += xDist/50;
    y += yDist/50;

    // random noise to make movement look real
    // y += (std::rand() / ((RAND_MAX + 1u) / 6));
    // x += (std::rand() / ((RAND_MAX + 1u) / 6));

}

void Enemy::detectHit(std::vector<Projectile> projectiles, Animator* animator, int64_t t)
{
    for(Projectile& p : projectiles)
    {
        if(std::abs(p.x - x) < 20 && std::abs(p.y - y) < 20)
        {
            OutputDebugStringA("hit!\n");
            // play explosion animation, and mark as to delete, and glow grid lines
            isActive = false; //does this need to be here?
            animator->gridRow = (int)y;// thse two lines mark an explosion
            animator->gridCol = (int)x;
            animator->startExplosion(x, y, t);
        }
    }
}

void Enemy::update(std::vector<Projectile> projectiles, Player* player, Animator* animator, int64_t timeElapsed, int64_t currTime)
{
    move(player, timeElapsed);
    detectHit(projectiles, animator, currTime);
}














void Enemy::draw(ID2D1HwndRenderTarget* renderTarget, Player* player)
{
    float xDistance = player->x - x;
    float yDistance = player->y - y;

    angle = ((float)atan(yDistance / xDistance) * (180.0f /PI)) + 45.0f;
    if(player->x < x) angle += 180; // not sure why, but this is important

    D2D1_POINT_2F center = {};
    center.x = x;
    center.y = y;

    renderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(angle, center));

    D2D1_SIZE_F enemy_size = bitmap->GetSize();
    renderTarget->DrawBitmap(bitmap, D2D1::RectF(
                x - (enemy_size.width / 2), 
                y - (enemy_size.height / 2), 
                x + (enemy_size.width / 2), 
                y + (enemy_size.height / 2)));
    
    renderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(0, center));
    
}