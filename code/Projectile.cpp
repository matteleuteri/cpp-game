#include "Projectile.h"


Projectile::Projectile(LPARAM lParam, float x2, float y2)
{
    speed = 1.0;
    direction[0] = LOWORD(lParam) - x2;
    direction[1] = HIWORD(lParam) - y2;

    // normalize
    float divisor = sqrt(pow(direction[0], 2) + pow(direction[1], 2));
    direction[0] /= divisor;
    direction[1] /= divisor;
    x = x2;
    y = y2;
    isActive = true;

}
Projectile::~Projectile()
{
    // delete player;
}







