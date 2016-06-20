//
// Created by martin on 31.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_EVOLUTIONANIMATION_HPP
#define POKEMON_CUSTOM_EVOLUTION_EVOLUTIONANIMATION_HPP

#include "Animation.hpp"
#include <src/images/BitMap.hpp>

using namespace Images;

namespace Engine
{
    namespace nsAnimation
    {
        namespace Animations
        {
            class EvolutionAnimation : public Animation
            {
            public:
                bool swap = false;
                bool changeToWhite = false;
                BitMapPtr &originalBitMap;
                BitMapPtr bitMap = nullptr;

                EvolutionAnimation(BitMapPtr &bitMap);
                ~EvolutionAnimation();
                virtual AnimationStatus Animate(float delta) override;
                void Fade(glm::vec3 color, float time, unsigned int yOffset);
                void Fade(BitMapPtr fadeBitMap, float time, unsigned int yOffset);
                void Fade(std::vector<BitMapPtr> &cachedBitMaps, float totalAnimTime, float animTime);
            };

            typedef std::shared_ptr<EvolutionAnimation> EvolutionAnimationPtr;
        }
    }
}
#endif //POKEMON_CUSTOM_EVOLUTION_EVOLUTIONANIMATION_HPP
