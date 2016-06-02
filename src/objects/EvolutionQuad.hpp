//
// Created by martin on 26.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_ANIMATEDQUAD_HPP
#define POKEMON_CUSTOM_EVOLUTION_ANIMATEDQUAD_HPP

#include <engine/animation/animations/EvolutionAnimation.hpp>
#include "Quad.hpp"

class EvolutionQuad : public Quad
{
private:
    BitMap *_firstStageOfEvolution;
    BitMap *_secondStageOfEvolution;
    bool _firstStageOfEvolutionIsActive;
    bool _secondStageOfEvolutionIsActive;
public:
    EvolutionAnimation *animation;

    EvolutionQuad(Loader *loader, glm::vec2 position, float scale, BitMap *firstStageOfEvolution, BitMap *secondStageOfEvolution);
    ~EvolutionQuad();
    void Animate(float delta) override ;
};

typedef std::shared_ptr<EvolutionQuad> EvolutionQuadPtr;

#endif //POKEMON_CUSTOM_EVOLUTION_ANIMATEDQUAD_HPP
