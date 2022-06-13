#include "headers/FireButton.h"

void FireButton::execute(std::unique_ptr<Scene>& scene)
{
    scene->player->speedScale = 2.0f; // will, or how will I set this back to 1?
}