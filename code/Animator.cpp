#include "headers/Animator.h"

Animator::Animator()
{
    explosionIndex = 0;
}

Animator::Animator(int64_t start, int x, int y): gridRow(y), gridCol(x) 
{
    explosionIndex = 0;
}
Animator::~Animator() {}

void Animator::startExplosion(float x, float y)
{
    int64_t timestamp = 1;
    // make small and large explosions dependeing on if the target is hit
    Explosion e(timestamp, x, y);
    e.isPlaying = true;
    e.bitmap = expBitmap;
    explosions.push_back(e);
}

void Animator::refreshAnimationFrame(){}

