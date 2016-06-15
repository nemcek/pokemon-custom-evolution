//
// Created by martin on 26.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_ANIMATION_HPP
#define POKEMON_CUSTOM_EVOLUTION_ANIMATION_HPP

#include <vector>
#include <engine/animation/keyframes/EvolutionKeyFrame.hpp>
#include "engine/animation/keyframes/KeyFrame.hpp"

using namespace Engine::nsAnimation::KeyFrames;

namespace Engine
{
    namespace nsAnimation
    {
        namespace Animations
        {
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
                void Init();

            protected:
                float animationTime;
                int currentKeyFrameIndex;
                bool delay = false;
                float delayTime = 0;

                float GetAnimationTime(int index);
                bool ShouldRepeat(int index);
                bool ShouldMoveToNextFrame(int index, float delta);
                void MoveToNextFrame();
                void CalculatePosition(int index, float time);
                void CalculateScale(int index, float time);

            };

            typedef std::shared_ptr<Animation> AnimationPtr;
        }
    }
}
#endif //POKEMON_CUSTOM_EVOLUTION_ANIMATION_HPP
