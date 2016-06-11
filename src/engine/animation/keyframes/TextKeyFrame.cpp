//
// Created by martin on 29.05.2016.
//

#include "TextKeyFrame.hpp"

namespace Engine
{
    namespace nsAnimation
    {
        namespace KeyFrames
        {
            TextKeyFrame::TextKeyFrame(float time, glm::vec2 pos, float scale, std::string text)
                    : KeyFrame(time, pos, scale),
                      text(text) {
            }

            TextKeyFrame::TextKeyFrame(float time, glm::vec2 pos, float scale, std::string text,
                                       std::function<void(void)> callback)
                    : KeyFrame(time, pos, scale, callback),
                      text(text) {
            }

            TextKeyFrame::~TextKeyFrame() {
            }
        }
    }
}