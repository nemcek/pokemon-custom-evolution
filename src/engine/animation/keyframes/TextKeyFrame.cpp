//
// Created by martin on 29.05.2016.
//

#include "TextKeyFrame.hpp"

TextKeyFrame::TextKeyFrame(float time, glm::vec2 pos, float scale, std::string text)
    : KeyFrame(time, pos, scale),
      text(text)
{
}