#ifndef _PROJECTILE
#define _PROJECTILE

#include <math.h>
#include <windows.h>
#include <d2d1.h>

class Projectile
{
public:
    float x;
    float y;
    float speed;
    float direction[2];
    float angle;
    bool isActive;
    ID2D1Bitmap* bitmap;
    Projectile::Projectile(LPARAM lparam, float x2, float y2, ID2D1Bitmap *b);
    Projectile::~Projectile();
};

#endif