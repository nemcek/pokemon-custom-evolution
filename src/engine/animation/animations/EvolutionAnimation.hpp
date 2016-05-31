//
// Created by martin on 31.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_EVOLUTIONANIMATION_HPP
#define POKEMON_CUSTOM_EVOLUTION_EVOLUTIONANIMATION_HPP

#include "Animation.hpp"
#include <src/images/BitMap.hpp>

class EvolutionAnimation : public Animation
{
public:
    bool swap = false;
    BitMap originalBitMap;
    BitMap *bitMap = nullptr;

    EvolutionAnimation(BitMap bitMap);
    AnimationStatus Animate(float delta) override ;
    void Fade(glm::vec3 color, float time);
};

#endif //POKEMON_CUSTOM_EVOLUTION_EVOLUTIONANIMATION_HPP
