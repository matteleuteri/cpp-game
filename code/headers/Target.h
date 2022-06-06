#ifndef _TARGET
#define _TARGET

#include <d2d1.h>

class Target
{
public:
    int x;
    int y;
    bool isHit;
    ID2D1Bitmap *bitmap;
    Target::Target();
    // must react to an enemy being hit in the same area
};

#endif