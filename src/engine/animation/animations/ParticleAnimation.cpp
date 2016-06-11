//
// Created by martin on 12.06.2016.
//

#include "ParticleAnimation.hpp"

namespace Engine
{
    namespace nsAnimation
    {
        namespace Animations
        {
            ParticleAnimation::ParticleAnimation(BitMapPtr &bitMap)
                : EvolutionAnimation(bitMap) { }

            ParticleAnimation::~ParticleAnimation() { }

            AnimationStatus ParticleAnimation::Animate(float delta) {
                EvolutionAnimation::Animate(delta);

                if (currentKeyFrameIndex + 1 >= keyFrames.size())
                    return AnimationStatus::Default;

                Move(std::static_pointer_cast<ParticleKeyFrame>(this->keyFrames[this->currentKeyFrameIndex])->pointCompound,
                     GetAnimationTime(currentKeyFrameIndex));

                return AnimationStatus::Default;
            }

            void ParticleAnimation::Move(PointCompound4 pointCompound, float time) {
                Point p;
                Transformations::Bezier(p, pointCompound.A, pointCompound.B, pointCompound.C, pointCompound.D, time);

                this->position.x = p.X;
                this->position.y = p.Y;
            }
        }
    }
}