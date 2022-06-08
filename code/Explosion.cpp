#include "headers/Explosion.h"

Explosion::Explosion(int64_t start, float xin, float yin, bool t): x(xin), y(yin), startTime(start), isPlaying(t)
{
    frameNum = 0;
}

void Explosion::flipFrame(std::array<ID2D1Bitmap*, 3> bitmaps)
{
    // if(bitmap == exp1Bitmap) 
    //     bitmap = exp2Bitmap;
    // else if(bitmap == exp2Bitmap) 
    //     bitmap = exp1Bitmap;
    bitmap = bitmaps[frameNum];
}