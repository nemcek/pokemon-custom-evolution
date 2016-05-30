//
// Created by martin on 31.05.2016.
//

#include <engine/animation/keyframes/EvolutionKeyFrame.hpp>
#include "EvolutionAnimation.hpp"

EvolutionAnimation::EvolutionAnimation()
{
}

AnimationStatus EvolutionAnimation::Animate(float delta)
{
    AnimationStatus status = Animation::Animate(delta);

    if (status == AnimationStatus::MovedToNext)
    {
        swap = static_cast<EvolutionKeyFrame *>(keyFrames[currentKeyFrameIndex])->swap;
    }

    return AnimationStatus::Default;
}