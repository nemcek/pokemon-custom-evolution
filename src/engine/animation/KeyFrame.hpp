//
// Created by martin on 26.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_KEYFRAME_HPP
#define POKEMON_CUSTOM_EVOLUTION_KEYFRAME_HPP

#include <glm/vec2.hpp>

class KeyFrame
{
public:
    glm::vec2 position;
    float time;
    float scale;

    KeyFrame(float time, glm::vec2 pos, float scale);
};

#endif //POKEMON_CUSTOM_EVOLUTION_KEYFRAME_HPP
