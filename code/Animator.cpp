#include "headers/Animator.h"

Animator::Animator(int64_t start, int x, int y, std::array<ID2D1Bitmap*, 12> bitmaps)
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
    score->bitmap = bitmaps[6]; //TODO: put in constructor !!!
    
    mountain = new Mountain(bitmaps[10], 700, 700);
    mountain->xMax = 800; //TODO: put in constructor !!!
    mountain->xMin = 600; //TODO: put in constructor !!!
    mountain->yMax = 800; //TODO: put in constructor !!!
    mountain->yMin = 600; //TODO: put in constructor !!!

    mountain2 = new Mountain(bitmaps[11], 700, 700);
    mountain2->xMax = 750; //TODO: put in constructor !!!
    mountain2->xMin = 650; //TODO: put in constructor !!!
    mountain2->yMax = 750; //TODO: put in constructor !!!
    mountain2->yMin = 650; //TODO: put in constructor !!!
}

void Animator::startExplosion(float x, float y, int64_t timestamp)
{
    //TODO make small and large explosions dependeing on if the target is hit
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

    score->flipFrame(scoreBitmaps, currentTime);
}
void Animator::showScore(int64_t currentTime)
{
    score->isActive = true;
    score->startTime = currentTime;
}

