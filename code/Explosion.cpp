#include "headers/Explosion.h"

Explosion::Explosion(int64_t start, float xin, float yin, bool t): x(xin), y(yin), startTime(start), isPlaying(t)
{
    frameNum = 0;
}

void Explosion::flipFrame(std::array<ID2D1Bitmap*, 3> bitmaps)
{
    bitmap = bitmaps[frameNum];
}