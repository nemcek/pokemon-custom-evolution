//
// Created by martin on 26.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_ANIMATION_HPP
#define POKEMON_CUSTOM_EVOLUTION_ANIMATION_HPP

#include <vector>
#include "KeyFrame.hpp"

class Animation
{
public:
    std::vector<KeyFrame *> keyFrames;
    glm::vec2 position;
    float scale;
    float animationTime;
    int i;
    bool repeat = true;

    Animation();
    bool Animate(float delta);
    void Add(KeyFrame *keyFrame);
    void Init();
};

#endif //POKEMON_CUSTOM_EVOLUTION_ANIMATION_HPP
