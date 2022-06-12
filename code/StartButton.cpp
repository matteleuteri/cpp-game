#include "headers/StartButton.h"

void StartButton::execute(std::unique_ptr<Scene>& scene)
{
    scene->isActive = !scene->isActive;
}