//
// Created by martin on 26.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_ANIMATEDQUAD_HPP
#define POKEMON_CUSTOM_EVOLUTION_ANIMATEDQUAD_HPP

#include <engine/animation/animations/Animation.hpp>
#include "Quad.hpp"

class AnimatedQuad : public Quad
{
public:
    Animation *animation;

    AnimatedQuad(Loader *loader, glm::vec2 position, float scale, BitMap *bitMap);
    void Animate(float delta) override ;
};

#endif //POKEMON_CUSTOM_EVOLUTION_ANIMATEDQUAD_HPP
