//
// Created by martin on 26.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_ANIMATION_HPP
#define POKEMON_CUSTOM_EVOLUTION_ANIMATION_HPP

#include <vector>
#include "engine/animation/keyframes/KeyFrame.hpp"

enum AnimationStatus
{
    MovedToNext,
    Skipped,
    Default
};

class Animation
{
private:

protected:
    float animationTime;
    int currentKeyFrameIndex;

    float GetAnimationTime(int index);
    void Init();
    bool ShouldRepeat(int index);
    bool ShouldMoveToNextFrame(int index, float delta);
    void MoveToNextFrame();
    void CalculatePosition(int index, float time);
    void CalculateScale(int index, float time);
public:
    std::vector<KeyFrame *> keyFrames;
    bool repeat = true;
    glm::vec2 position;
    float scale;

    Animation();
    Animation(bool repeat);
    virtual AnimationStatus Animate(float delta);
    void Add(KeyFrame *keyFrame);
};

#endif //POKEMON_CUSTOM_EVOLUTION_ANIMATION_HPP