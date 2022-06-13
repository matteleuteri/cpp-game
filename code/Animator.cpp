#include "headers/Animator.h"

Animator::Animator(int64_t start, int x, int y, std::array<ID2D1Bitmap*, 10> bitmaps)
{
    gridRow = y;
    gridCol = x;
    explosionIndex = 0;
    scoreBitmaps[0] = bitmaps[6];
    scoreBitmaps[1] = bitmaps[7];
    scoreBitmaps[2] = bitmaps[8];
    scoreBitmaps[3] = bitmaps[9];
    explosionBitmaps[0] = bitmaps[3];
    explosionBitmaps[1] = bitmaps[4];
    explosionBitmaps[2] = bitmaps[5];
    isActive = false;
    
    score = new Score();
    score->bitmap = bitmaps[6];
}

void Animator::startExplosion(float x, float y, int64_t timestamp)
{
    // make small and large explosions dependeing on if the target is hit
    Explosion e(timestamp, x, y, true);
    e.duration = 2400000;
    e.bitmap = explosionBitmaps[0];
    e.frameNum = 0;
    explosions.push_back(e);
}

void Animator::refreshAnimationFrame(int64_t currentTime)
{
    for(int index = 0; index < explosions.size(); index++) 
    {
        //TODO: BUG: wrong ineqwualities on explosion animation frame, flipping at unexpected rate
        Explosion* explosion = &explosions[index];
        if(currentTime - explosion->startTime < 800000)
        {
            explosion->frameNum = 1;
            explosion->flipFrame(explosionBitmaps);
        }
        else if(currentTime - explosion->startTime < 1600000)
        {
            explosion->frameNum = 2;
            explosion->flipFrame(explosionBitmaps);
        }
        else if(currentTime - explosion->startTime < explosion->duration)
        {
            explosions.erase(explosions.begin() + index);
        }
    }   

    if(currentTime - score->startTime < 800000)
    {
        score->frameNum = 0;
        score->flipFrame(scoreBitmaps);
    }
    else if(currentTime - score->startTime < 1600000)
    {
        score->frameNum = 1;
        score->flipFrame(scoreBitmaps);
    }
    else if(currentTime - score->startTime < 2400000)
    {
        score->frameNum = 2;
        score->flipFrame(scoreBitmaps);
    }
    else if(currentTime - score->startTime < 3200000)
    {
        score->frameNum = 3;
        score->flipFrame(scoreBitmaps);
        score->startTime = currentTime;
    }

}
void Animator::showScore(int64_t currentTime)
{
    score->isActive = true;
    score->startTime = currentTime;
}

