#ifndef _MOUNTAIN
#define _MOUNTAIN

#include <d2d1.h>
#include "../../headers/Player.h"

class Mountain
{
public:
    ID2D1Bitmap *bitmap;
    float x;
    float y;
    float xMin;
    float xMax;
    float yMin;
    float yMax;
    Mountain::Mountain(ID2D1Bitmap* b, float x, float y);

    void Mountain::update(Player* player, int64_t timeElapsed);
};

#endif _MOUNTAIN