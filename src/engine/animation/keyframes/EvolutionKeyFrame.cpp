//
// Created by martin on 31.05.2016.
//

#include "EvolutionKeyFrame.hpp"

namespace Engine
{
    namespace nsAnimation
    {
        namespace KeyFrames
        {
            EvolutionKeyFrame::EvolutionKeyFrame(float time, glm::vec2 pos, float scale, bool swap)
                    : KeyFrame(time, pos, scale) {
                this->swap = swap;
            }

            EvolutionKeyFrame::EvolutionKeyFrame(float time, glm::vec2 pos, float scale, std::function<void(void)> callback,
                                                 bool swap)
                    : KeyFrame(time, pos, scale, callback) {
                this->swap = swap;
            }

            EvolutionKeyFrame::EvolutionKeyFrame(float time, glm::vec2 pos, float scale, glm::vec3 color, unsigned int yColorOffset,
                                                 bool swap, bool changeToWhite)
                    : KeyFrame(time, pos, scale)
                    , yColorOffset(yColorOffset)
                    , changeToWhite(changeToWhite) {
                this->color = color;
                this->colorEnabled = true;
                this->swap = swap;
            }

            EvolutionKeyFrame::EvolutionKeyFrame(float time, glm::vec2 pos, float scale, BitMapPtr fadeBitMap, unsigned int yColorOffset,
                                                 bool swap, bool changeToWhite)
                    : KeyFrame(time, pos, scale)
                    , yColorOffset(yColorOffset)
                    , changeToWhite(changeToWhite)
                    , fadeBitMap(fadeBitMap) {
                this->colorEnabled = true;
                this->swap = swap;
            }

            EvolutionKeyFrame::EvolutionKeyFrame(float time, glm::vec2 pos, float scale, glm::vec3 color, unsigned int yColorOffset,
                                                 std::function<void(void)> callback, bool swap)
                    : KeyFrame(time, pos, scale, callback)
                    , yColorOffset(yColorOffset) {
                this->color = color;
                this->colorEnabled = true;
                this->swap = swap;
            }

            EvolutionKeyFrame::~EvolutionKeyFrame() {
            }
        }
    }
}