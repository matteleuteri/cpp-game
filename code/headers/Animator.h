#ifndef _ANIMATOR
#define _ANIMATOR

#include <stdint.h>
#include <vector>
#include <Objbase.h>

#include "Explosion.h"
#include "Score.h"

class Animator
{
public:
    bool isActive;
    int gridRow;
    int gridCol;
    int explosionIndex;
    // int scoreValue;
    Score* score;

    std::vector<Explosion> explosions;
    std::array<ID2D1Bitmap*, 3> explosionBitmaps;
    std::array<ID2D1Bitmap*, 4> scoreBitmaps;

    Animator::Animator(int64_t start, int x, int y, std::array<ID2D1Bitmap*, 10> bitmaps);
    // Animator::Animator();
    void Animator::showScore(int64_t currentTime);
    void Animator::startExplosion(float x, float y, int64_t timestamp);
    void Animator::refreshAnimationFrame(int64_t currentTime);
};

#endif