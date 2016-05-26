//
// Created by martin on 26.05.2016.
//

#include <engine/Transformations.hpp>
#include "Animation.hpp"

Animation::Animation()
{
}

void Animation::Init()
{
    i = 0;
    animationTime = 0;
}

void Animation::Add(KeyFrame *keyFrame)
{
    this->keyFrames.push_back(keyFrame);
}

bool Animation::Animate(float delta)
{
    if (i + 1 >= this->keyFrames.size())
    {
        if (repeat)
            Init();
        else
            return false;
    }

    float t = animationTime / (keyFrames[i + 1]->time - keyFrames[i]->time);

    position = Transformations::Lerp(keyFrames[i]->position, keyFrames[i + 1]->position, t);
    scale = Transformations::Lerp(keyFrames[i]->scale, keyFrames[i + 1]->scale, t);
    animationTime += delta;

    if (animationTime > (keyFrames[i + 1]->time - keyFrames[i]->time) + delta)
    {
        i++;
        animationTime = 0;

        position = keyFrames[i]->position;
    }

    return true;
}