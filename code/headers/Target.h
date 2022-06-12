#ifndef _TARGET
#define _TARGET

#include <d2d1.h>
#include "Animator.h"

class Target
{
public:
    int x;
    int y;
    bool isHit;
    ID2D1Bitmap *bitmap;
    Target::Target(int startX, int startY);
    void Target::update(Animator *animator, int64_t t);
    // must react to an enemy being hit in the same area
};

#endif