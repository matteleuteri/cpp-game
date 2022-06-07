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
    ID2D1Bitmap *expBitmap;

    // Explosion* explosions[10];

    Animator::Animator(int64_t start, int x, int y);
    Animator::~Animator();
    Animator::Animator();
    void Animator::startExplosion(float x, float y);
    void Animator::refreshAnimationFrame();
};

#endif