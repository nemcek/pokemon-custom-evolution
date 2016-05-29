//
// Created by martin on 26.05.2016.
//

#include "KeyFrame.hpp"

KeyFrame::KeyFrame(float time, glm::vec2 pos, float scale)
{
    this->time = time;
    this->position = pos;
    this->scale = scale;
}