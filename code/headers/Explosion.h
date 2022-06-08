#ifndef _EXPLOSION
#define _EXPLOSION

#include <stdint.h>
#include <d2d1.h>
#include <array>

class Explosion
{
public:
    float x;
    float y;
    bool isPlaying; // should just be playing for it's entire dration, then get deleted
    int frameNum;

    ID2D1Bitmap *bitmap;
    int64_t startTime;
    int64_t duration;

    void Explosion::flipFrame(ID2D1Bitmap *exp1Bitmap, ID2D1Bitmap *exp2Bitmap);
    Explosion::Explosion(int64_t start, float xin, float yin, bool t);
}; 

#endif