//
// Created by martin on 26.05.2016.
//

#include <engine/Transformations.hpp>
#include "Animation.hpp"

namespace Engine
{
    namespace nsAnimation
    {
        namespace Animations
        {
            Animation::Animation() {
                Init();
                this->enabled = true;
            }

            Animation::Animation(bool repeat) : Animation() {
                this->repeat = repeat;
            }

            Animation::~Animation() {
                this->keyFrames.clear();
            }

            void Animation::Init() {
                currentKeyFrameIndex = 0;
                animationTime = 0;
            }

            void Animation::Add(KeyFramePtr keyFrame) {
                this->keyFrames.push_back(keyFrame);
            }

            KeyFramePtr Animation::GetLastKetFrame() {
                return this->keyFrames[this->keyFrames.size() - 1];
            }

            float Animation::GetAnimationTime(int index) {
                return animationTime / (keyFrames[index + 1]->time - keyFrames[index]->time);
            }

            bool Animation::ShouldRepeat(int index) {
                if (index + 1 >= this->keyFrames.size()) {
                    if (repeat)
                        Init();
                    else
                        return false;
                }

                return true;
            }

            bool Animation::ShouldMoveToNextFrame(int index, float delta) {
                return (animationTime > (keyFrames[index + 1]->time - keyFrames[index]->time) + delta);
            }

            void Animation::MoveToNextFrame() {
                currentKeyFrameIndex++;
                animationTime = 0;
            }

            AnimationStatus Animation::Animate(float delta) {
                position = keyFrames[currentKeyFrameIndex]->position;
                scale = keyFrames[currentKeyFrameIndex]->scale;

                if (!enabled)
                    return AnimationStatus::Skipped;

                if (!ShouldRepeat(currentKeyFrameIndex))
                    return AnimationStatus::Skipped;

                if (delay) {
                    animationTime += delta;

                    if (animationTime > delayTime) {
                        delay = false;
                        animationTime = 0;
                    }

                    return AnimationStatus::Skipped;
                }

                float t = GetAnimationTime(currentKeyFrameIndex);

                CalculatePosition(currentKeyFrameIndex, t);
                CalculateScale(currentKeyFrameIndex, t);
                animationTime += delta;

                if (ShouldMoveToNextFrame(currentKeyFrameIndex, delta)) {
                    MoveToNextFrame();
                    position = keyFrames[currentKeyFrameIndex]->position;
                    scale = keyFrames[currentKeyFrameIndex]->scale;

                    if (keyFrames[currentKeyFrameIndex]->callback != nullptr)
                        keyFrames[currentKeyFrameIndex]->callback();

                    return AnimationStatus::MovedToNext;
                }

                return AnimationStatus::Default;
            }

            void Animation::CalculatePosition(int index, float time) {
                this->position = Transformations::Lerp(keyFrames[index]->position, keyFrames[index + 1]->position,
                                                       time);
            }

            void Animation::CalculateScale(int index, float time) {
                this->scale = Transformations::Lerp(keyFrames[index]->scale, keyFrames[index + 1]->scale, time);
            }

            void Animation::SetDelay(float delayTime) {
                this->delay = true;
                this->delayTime = delayTime;
            }
        }
    }
}