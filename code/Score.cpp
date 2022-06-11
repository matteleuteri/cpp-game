#include "headers/Score.h"

Score::Score()
{
    x=200;
    y=200;
    isActive = false;
    frameNum = 0;
}

void Score::flipFrame(std::array<ID2D1Bitmap*, 4> bitmaps)
{
    bitmap = bitmaps[frameNum];
}