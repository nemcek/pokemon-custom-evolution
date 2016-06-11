//
// Created by martin on 26.05.2016.
//

#include "KeyFrame.hpp"

namespace Engine
{
    namespace nsAnimation
    {
        namespace KeyFrames
        {
            KeyFrame::KeyFrame(float time, glm::vec2 pos, float scale) {
                Init(time, pos, scale);
            }

            KeyFrame::KeyFrame(float time, glm::vec2 pos, float scale, std::function<void(void)> callback) {
                Init(time, pos, scale);
                this->callback = callback;
            }

            KeyFrame::~KeyFrame() {
            }

            void KeyFrame::Init(float time, glm::vec2 pos, float scale) {
                this->time = time;
                this->position = pos;
                this->scale = scale;
            }
        }
    }
}