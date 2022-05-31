#ifndef _PROJECTILE
#define _PROJECTILE

#include <windows.h> // for point type
class Projectile
{
public:
    float x;
    float y;
    float speed;
    float direction[2];
    Projectile::Projectile();
};


#endif
