#include "headers/Animator.h"

Animator::Animator()
{
    explosionIndex = 0;
    scoreValue = 0;
    isActive = false;
    score = new Score();
    // score->bitmap = ;
}

Animator::Animator(int64_t start, int x, int y): gridRow(y), gridCol(x) 
{
    explosionIndex = 0;
    scoreValue = 0;
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
        }
        if(currentTime - explosion->startTime > 1600000)
        {
            explosion->frameNum = 2;
            explosion->flipFrame(explosionBitmaps);
        }
        if(currentTime - explosion->startTime > explosion->duration)
        {
            explosions.erase(explosions.begin() + index);
        }
    }   
}
void Animator::showScore(int64_t currentTime)
{
    // collect bitmap(s) needed to display the score, at key frame 1
    // scoreObj

    score->bitmap = scoreBitmaps[0];
    score->isActive = true;


        // if(currentTime - explosion->startTime > 800000)
        // {
        //     explosion->frameNum = 1;
        //     explosion->flipFrame(explosionBitmaps);
        // }
        // if(currentTime - explosion->startTime > 1600000)
        // {
        //     explosion->frameNum = 2;
        //     explosion->flipFrame(explosionBitmaps);
        // }
        // if(currentTime - explosion->startTime > explosion->duration)
        // {
        //     score->isActive = false;
        // }

}

