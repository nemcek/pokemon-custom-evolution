//
// Created by martin on 31.05.2016.
//

#include "EvolutionKeyFrame.hpp"

EvolutionKeyFrame::EvolutionKeyFrame(float time, glm::vec2 pos, float scale, bool swap)
    : KeyFrame(time, pos, scale)
{
    this->swap = swap;
}