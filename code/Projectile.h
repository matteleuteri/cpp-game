#ifndef _PROJECTILE
#define _PROJECTILE
#include <math.h>

#include <windows.h> // for point type

class Projectile
{
public:
    float x;
    float y;
    float speed;
    float direction[2];
    bool isActive;
    Projectile::Projectile(LPARAM lparam, float xy, float y2);
    Projectile::~Projectile();

};


#endif
