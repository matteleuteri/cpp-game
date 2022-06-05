#include "headers/Projectile.h"


Projectile::Projectile(LPARAM lParam, float x2, float y2, ID2D1Bitmap *b)
{
    // consider using an angle instead of direction vector
    bitmap = b;
    speed = 1.0;
    direction[0] = LOWORD(lParam) - x2;
    direction[1] = HIWORD(lParam) - y2;

    // gety the angle


    angle = ((float)atan(direction[1] / direction[0]) * (180.0f /3.141592653589793238463f )) + 90.0f; // offset needed to define origin rotation angle 

    if(LOWORD(lParam) < x2) angle += 180; // not sure why, but this is important




    // normalize
    float divisor = (float)sqrt(pow(direction[0], 2) + pow(direction[1], 2));
    direction[0] /= divisor;
    direction[1] /= divisor;
    x = x2;
    y = y2;
    isActive = true;
}

Projectile::~Projectile()
{}
