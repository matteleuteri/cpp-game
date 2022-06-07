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
    Explosion e(timestamp, x, y);
    e.isPlaying = true;
    e.bitmap = exp1Bitmap;
    explosions.push_back(e);
}

void Animator::refreshAnimationFrame(int64_t currentTime)
{
    // for eveery explosion do this
    for(auto& explosion: explosions) 
    {
        if(currentTime - explosion.startTime > 200000)
        {
            if(explosion.bitmap == exp1Bitmap) 
                explosion.bitmap = exp2Bitmap;
            else if(explosion.bitmap == exp2Bitmap) 
                explosion.bitmap = exp1Bitmap;
            explosion.startTime = currentTime;
        }
    }   
}

