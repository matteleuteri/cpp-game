#ifndef _ANIMATOR
#define _ANIMATOR

#include <stdint.h>
#include <vector>
#include <Objbase.h>

#include "Explosion.h"

class Animator
{
public:
    bool isActive;
    int gridRow;
    int gridCol;
    int explosionIndex;
    std::vector<Explosion> explosions;
    ID2D1Bitmap *exp1Bitmap;
    ID2D1Bitmap *exp2Bitmap;

    // Explosion* explosions[10];

    Animator::Animator(int64_t start, int x, int y);
    Animator::Animator();
    void Animator::startExplosion(float x, float y, int64_t timestamp);
    void Animator::refreshAnimationFrame(int64_t currentTime);
};

#endif