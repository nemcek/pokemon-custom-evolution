//
// Created by martin on 14.06.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_EVOLUTIONPARTICLEGENERATOR_HPP
#define POKEMON_CUSTOM_EVOLUTION_EVOLUTIONPARTICLEGENERATOR_HPP

#include "EvolutionParticle.hpp"

namespace Objects
{
    class EvolutionParticleGenerator
    {
    public:
        static std::vector<EvolutionParticlePtr>* GenerateFlyArounds(LoaderPtr loader);
    };
}

#endif //POKEMON_CUSTOM_EVOLUTION_EVOLUTIONPARTICLEGENERATOR_HPP
