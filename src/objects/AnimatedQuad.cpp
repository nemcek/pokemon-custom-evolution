//
// Created by martin on 26.05.2016.
//

#include "AnimatedQuad.hpp"

AnimatedQuad::AnimatedQuad(Loader *loader, glm::vec2 position, float scale, BitMap *bitMap)
    : Quad(loader, position, scale, bitMap)
{
}

void AnimatedQuad::Animate(float delta)
{
    if (this->animation != nullptr)
    {
        this->animation->Animate(delta);
        this->position = this->animation->position;
        this->Scale(this->animation->scale);
    }
}
