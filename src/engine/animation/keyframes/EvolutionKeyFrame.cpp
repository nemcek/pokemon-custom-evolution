//
// Created by martin on 31.05.2016.
//

#include "EvolutionKeyFrame.hpp"

EvolutionKeyFrame::EvolutionKeyFrame(float time, const glm::vec2 pos, float scale, bool swap)
    : KeyFrame(time, pos, scale)
{
    this->swap = swap;
}

EvolutionKeyFrame::EvolutionKeyFrame(float time, const glm::vec2 pos, float scale, const glm::vec3 color, bool swap)
        : KeyFrame(time, pos, scale)
{
    this->color = color;
    this->colorEnabled = true;
    this->swap = swap;
}

EvolutionKeyFrame::EvolutionKeyFrame(float time, const glm::vec2 pos, float scale, const glm::vec3 color,
                                     std::function<void(void)> callback, bool swap)
    : KeyFrame(time, pos, scale, callback)
{
    this->color = color;
    this->colorEnabled = true;
    this->swap = swap;
}

EvolutionKeyFrame::~EvolutionKeyFrame()
{
}