#include "headers/Animator.h"

Animator::Animator()
{
    explosionIndex = 0;
}

Animator::Animator(int64_t start, int x, int y): gridRow(y), gridCol(x) 
{
    explosionIndex = 0;
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
        Explosion* explosion = &explosions[index];
        if(currentTime - explosion->startTime > 800000)
        {
            explosion->frameNum = 1;
            explosion->flipFrame(explosionBitmaps);
            // explosion->bitmap = explosionBitmaps[1];
        }
        if(currentTime - explosion->startTime > 1600000)
        {
            explosion->frameNum = 2;
            explosion->flipFrame(explosionBitmaps);
            // explosion->bitmap = explosionBitmaps[1];
        }
        if(currentTime - explosion->startTime > explosion->duration)
        {
            explosions.erase(explosions.begin() + index);
        }
    }   
}

