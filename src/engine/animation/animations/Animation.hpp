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
public:
    std::vector<KeyFramePtr> keyFrames;
    bool repeat = true;
    glm::vec2 position;
    float scale;
    bool enabled;

    Animation();
    Animation(bool repeat);
    virtual ~Animation();
    virtual AnimationStatus Animate(float delta);
    void Add(KeyFramePtr keyFrame);
    void SetDelay(float delayTime);

protected:
    float animationTime;
    int currentKeyFrameIndex;
    bool delay = false;
    float delayTime = 0;

    float GetAnimationTime(int index);
    void Init();
    bool ShouldRepeat(int index);
    bool ShouldMoveToNextFrame(int index, float delta);
    void MoveToNextFrame();
    void CalculatePosition(int index, float time);
    void CalculateScale(int index, float time);

private:

};

typedef std::shared_ptr<Animation> AnimationPtr;

#endif //POKEMON_CUSTOM_EVOLUTION_ANIMATION_HPP
