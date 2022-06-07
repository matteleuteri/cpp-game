#ifndef _EXPLOSION
#define _EXPLOSION

#include <stdint.h>
#include <d2d1.h>

class Explosion
{
public:
    float x;
    float y;
    bool isPlaying;
    ID2D1Bitmap *bitmap;
    int64_t startTime;
    Explosion::Explosion(int64_t start, float xin, float yin);
}; 

#endif