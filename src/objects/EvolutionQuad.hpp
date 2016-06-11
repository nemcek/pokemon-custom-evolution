//
// Created by martin on 26.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_ANIMATEDQUAD_HPP
#define POKEMON_CUSTOM_EVOLUTION_ANIMATEDQUAD_HPP

#include <engine/animation/animations/EvolutionAnimation.hpp>
#include "Quad.hpp"

namespace Objects
{
    class EvolutionQuad : public Quad
    {
    private:
        BitMapPtr _firstStageOfEvolution;
        BitMapPtr _secondStageOfEvolution;
        bool _firstStageOfEvolutionIsActive;
        bool _secondStageOfEvolutionIsActive;
    public:
        EvolutionAnimationPtr animation;

        EvolutionQuad(LoaderPtr loader, glm::vec2 position, float scale, BitMapPtr firstStageOfEvolution,
                      BitMapPtr secondStageOfEvolution);

        ~EvolutionQuad();

        void Animate(float delta) override;
    };

    typedef std::shared_ptr<EvolutionQuad> EvolutionQuadPtr;
}
#endif //POKEMON_CUSTOM_EVOLUTION_ANIMATEDQUAD_HPP
