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
    void Target::checkIfHit(Animator *animator);

    ID2D1Bitmap *bitmap;
    Target::Target();
    // must react to an enemy being hit in the same area
};

#endif