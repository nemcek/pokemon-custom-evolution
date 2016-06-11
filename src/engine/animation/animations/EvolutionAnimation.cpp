//
// Created by martin on 31.05.2016.
//

#include <engine/animation/keyframes/EvolutionKeyFrame.hpp>
#include <engine/Transformations.hpp>
#include "EvolutionAnimation.hpp"

namespace Engine
{
    namespace nsAnimation
    {
        namespace Animations
        {
            EvolutionAnimation::EvolutionAnimation(BitMapPtr &bitMap) : Animation(), originalBitMap(bitMap) {
            }

            EvolutionAnimation::~EvolutionAnimation() {
            }

            AnimationStatus EvolutionAnimation::Animate(float delta) {
                AnimationStatus status = Animation::Animate(delta);

                if (status == AnimationStatus::Default || status == AnimationStatus::MovedToNext) {
                    if (currentKeyFrameIndex + 1 >= keyFrames.size())
                        return AnimationStatus::Default;

                    if (std::static_pointer_cast<EvolutionKeyFrame>(
                            keyFrames[currentKeyFrameIndex + 1])->colorEnabled) {
                        float t = GetAnimationTime(currentKeyFrameIndex);
                        Fade(std::static_pointer_cast<EvolutionKeyFrame>(keyFrames[currentKeyFrameIndex + 1])->color,
                             t);
                    }

                    if (status == AnimationStatus::MovedToNext) {
                        swap = std::static_pointer_cast<EvolutionKeyFrame>(keyFrames[currentKeyFrameIndex])->swap;
                        return status;
                    }
                }

                return AnimationStatus::Default;
            }

            void EvolutionAnimation::Fade(glm::vec3 color, float time) {
                bitMap = Transformations::Fade(originalBitMap, color, 286, time);
            }
        }
    }
}