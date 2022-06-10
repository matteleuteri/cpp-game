#ifndef _SCORE
#define _SCORE

#include <d2d1.h>
#include <array>

class Score
{
public:
    //need a bitmap. score, and coordinates
    ID2D1Bitmap* bitmap;
    Score::Score();
    bool isActive;
    int64_t startTime;
    float x;
    float y;
    int frameNum;
    void Score::flipFrame(std::array<ID2D1Bitmap*, 4> bitmaps);

};

#endif