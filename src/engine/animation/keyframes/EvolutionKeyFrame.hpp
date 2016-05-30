//
// Created by martin on 31.05.2016.
//

#include "KeyFrame.hpp"

#ifndef POKEMON_CUSTOM_EVOLUTION_EVOLUTIONKEYFRAME_HPP
#define POKEMON_CUSTOM_EVOLUTION_EVOLUTIONKEYFRAME_HPP

class EvolutionKeyFrame : public KeyFrame
{
public:
    bool swap = false;

    EvolutionKeyFrame(float time, glm::vec2 pos, float scale, bool swap = false);
};

#endif //POKEMON_CUSTOM_EVOLUTION_EVOLUTIONKEYFRAME_HPP
