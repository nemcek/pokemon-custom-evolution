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

                    EvolutionKeyFramePtr evoKeyFrame = std::static_pointer_cast<EvolutionKeyFrame>(keyFrames[currentKeyFrameIndex + 1]);

                    if (evoKeyFrame->colorEnabled) {
                        float t = GetAnimationTime(currentKeyFrameIndex);

                        if (evoKeyFrame->cachedBitMaps != nullptr) {
                            Fade(*evoKeyFrame->cachedBitMaps, evoKeyFrame->time - keyFrames[currentKeyFrameIndex]->time, animationTime);
                        }
                        else if (evoKeyFrame->fadeBitMap != nullptr) {
                            Fade(evoKeyFrame->fadeBitMap, t, evoKeyFrame->yColorOffset);
                        }
                        else {
                            Fade(evoKeyFrame->color, t, evoKeyFrame->yColorOffset);
                        }
                    }

                    if (status == AnimationStatus::MovedToNext) {
                        swap = std::static_pointer_cast<EvolutionKeyFrame>(keyFrames[currentKeyFrameIndex])->swap;
                        changeToWhite = std::static_pointer_cast<EvolutionKeyFrame>(keyFrames[currentKeyFrameIndex])->changeToWhite;

                        return status;
                    }
                }

                return AnimationStatus::Default;
            }

            void EvolutionAnimation::Fade(glm::vec3 color, float time, unsigned int yOffset) {
                bitMap = Transformations::Fade(originalBitMap, color, yOffset, time);
            }

            void EvolutionAnimation::Fade(BitMapPtr fadeBitMap, float time, unsigned int yOffset) {
                bitMap = Transformations::Fade(originalBitMap, fadeBitMap, yOffset, time);
            }

            void EvolutionAnimation::Fade(std::vector<BitMapPtr> &cachedBitMaps, float totalAnimTime, float animTime) {
                float cachedBitMapsCount = cachedBitMaps.size();
                float oneCachedBitMapTimePortion = totalAnimTime / cachedBitMapsCount;
                int idx = static_cast<int>(animTime / oneCachedBitMapTimePortion);

                bitMap = cachedBitMaps[idx];
            }
        }
    }
}