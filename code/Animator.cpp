#include "headers/Animator.h"

Animator::Animator(){}

Animator::Animator(int x, int y)
{
    row = y;
    col = x;
}
Animator::~Animator(){}

void Animator::startExplosion(float x, float y)
{
    row = (int)y;
    col = (int)x;
}