#include "headers/Explosion.h"

Explosion::Explosion(int64_t start, float xin, float yin): x(xin), y(yin), startTime(start)
{
    isPlaying = false;
}
