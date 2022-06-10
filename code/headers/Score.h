#ifndef _SCORE
#define _SCORE

#include <d2d1.h>

class Score
{
public:
    //need a bitmap. score, and coordinates
    ID2D1Bitmap* bitmap;
    Score::Score();
    bool isActive;
    float x;
    float y;
};

#endif