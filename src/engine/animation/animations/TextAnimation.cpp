//
// Created by martin on 29.05.2016.
//

#include <engine/animation/keyframes/TextKeyFrame.hpp>
#include <engine/Transformations.hpp>
#include "TextAnimation.hpp"

TextAnimation::TextAnimation()
{
}

TextAnimation::TextAnimation(bool repeat) : Animation(repeat)
{
}

TextAnimation::~TextAnimation()
{
}

AnimationStatus TextAnimation::Animate(float delta)
{
    AnimationStatus status = Animation::Animate(delta);

    if (status == AnimationStatus::Skipped)
        return status;
    else
    {
        if (status == AnimationStatus::Default || status == AnimationStatus::MovedToNext)
        {
            if (currentKeyFrameIndex + 1 >= keyFrames.size())
                return AnimationStatus::Default;

            float t = GetAnimationTime(currentKeyFrameIndex);
            TextKeyFramePtr nextKeyFrame = std::static_pointer_cast<TextKeyFrame>(keyFrames[currentKeyFrameIndex + 1]);

            float sourceTextLength = (float) std::static_pointer_cast<TextKeyFrame>(keyFrames[currentKeyFrameIndex])->text.length();
            float destinationTextLength = (float) nextKeyFrame->text.length();
            int substringLength = (int) Transformations::Lerp(sourceTextLength, destinationTextLength, t);

            text = nextKeyFrame->text.substr(0, (unsigned long) substringLength);

            if (status == AnimationStatus::MovedToNext)
            {
                text = std::static_pointer_cast<TextKeyFrame>(keyFrames[currentKeyFrameIndex])->text;
            }
        }
    }

    return AnimationStatus::Default;
}