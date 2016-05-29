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

bool TextAnimation::Animate(float delta)
{
    if (!ShouldRepeat(currentKeyFrameIndex))
        return false;

    float t = GetAnimationTime(currentKeyFrameIndex);
    TextKeyFrame *nextKeyFrame = static_cast<TextKeyFrame *>(keyFrames[currentKeyFrameIndex + 1]);

    float sourceTextLength = (float)static_cast<TextKeyFrame *>(keyFrames[currentKeyFrameIndex])->text.length();
    float destinationTextLength = (float)nextKeyFrame->text.length();
    int substringLength = (int)Transformations::Lerp(sourceTextLength, destinationTextLength, t);

    text = nextKeyFrame->text.substr(0, (unsigned long)substringLength);
    CalculatePosition(currentKeyFrameIndex, t);
    CalculateScale(currentKeyFrameIndex, t);
    animationTime += delta;

    if (ShouldMoveToNextFrame(currentKeyFrameIndex, delta))
    {
        MoveToNextFrame();
        text = nextKeyFrame->text;
    }

    return true;
}