#ifndef _ANIMATOR
#define _ANIMATOR

class Animator
{
public:
    bool isActive;
    int row;
    int col;

    Animator::Animator(int x, int y);
    Animator::~Animator();
    Animator::Animator();
    void Animator::startExplosion(float x, float y);
};

#endif