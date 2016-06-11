//
// Created by martin on 11.06.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_EVOLUTIONPARTICLE_HPP
#define POKEMON_CUSTOM_EVOLUTION_EVOLUTIONPARTICLE_HPP

#include <engine/animation/animations/ParticleAnimation.hpp>
#include "EvolutionQuad.hpp"

namespace Objects
{
    class EvolutionParticle : public EvolutionQuad
    {
    public:
        EvolutionParticle(LoaderPtr loader, glm::vec2 position, float scale, BitMapPtr firstStage,
            BitMapPtr secondStage, BitMapPtr thirdStage);

        void Animate(float delta) override;
    private:
        BitMapPtr _thirdsStage;
        bool _thirdStageIsActive;
    };

    typedef std::shared_ptr<EvolutionParticle> EvolutionParticlePtr;
}

#endif //POKEMON_CUSTOM_EVOLUTION_EVOLUTIONPARTICLE_HPP
