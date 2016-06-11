//
// Created by martin on 12.06.2016.
//

#include <engine/animation/keyframes/ParticleKeyFrame.hpp>
#include "EvolutionAnimation.hpp"

#ifndef POKEMON_CUSTOM_EVOLUTION_PARTICLEANIMATION_HPP
#define POKEMON_CUSTOM_EVOLUTION_PARTICLEANIMATION_HPP

namespace Engine
{
    namespace nsAnimation
    {
        namespace Animations
        {
            class ParticleAnimation : public EvolutionAnimation
            {
            public:
                ParticleAnimation(BitMapPtr &bitMap);
                ~ParticleAnimation();
                virtual AnimationStatus Animate(float delta) override;
                void Move(PointCompound4 pointCompound, float time);
            };
        }
    }
}

#endif //POKEMON_CUSTOM_EVOLUTION_PARTICLEANIMATION_HPP
