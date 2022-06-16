#include "headers/Score.h"

Score::Score()
{
    x=200;
    y=200;
    isActive = false;
    frameNum = 0;
}

void Score::flipFrame(std::array<ID2D1Bitmap*, 4> bitmaps, int64_t currentTime)
{
        if(currentTime - startTime < 800000)
    {
        frameNum = 0;
        bitmap = bitmaps[frameNum];
    }
    else if(currentTime - startTime < 1600000)
    {
        frameNum = 1;
        bitmap = bitmaps[frameNum];
    }
    else if(currentTime - startTime < 2400000)
    {
        frameNum = 2;
        bitmap = bitmaps[frameNum];
    }
    else if(currentTime - startTime < 3200000)
    {
        frameNum = 3;
        bitmap = bitmaps[frameNum];
        startTime = currentTime;
    }
    
}