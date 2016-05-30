//
// Created by martin on 31.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_EVOLUTIONANIMATION_HPP
#define POKEMON_CUSTOM_EVOLUTION_EVOLUTIONANIMATION_HPP

#include "Animation.hpp"

class EvolutionAnimation : public Animation
{
public:
    bool swap = false;

    EvolutionAnimation();
    AnimationStatus Animate(float delta) override ;
};

#endif //POKEMON_CUSTOM_EVOLUTION_EVOLUTIONANIMATION_HPP
