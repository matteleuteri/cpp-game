#include "headers/Animator.h"


Animator::Animator(int x, int y)
{
    row = y;
    col = x;
}
Animator::~Animator(){}

void Animator::startExplosion(float x, float y)
{
    row = y;
    col = x;
}