//
// Created by martin on 14.06.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_EVOLUTIONPARTICLEGENERATOR_HPP
#define POKEMON_CUSTOM_EVOLUTION_EVOLUTIONPARTICLEGENERATOR_HPP

#include "EvolutionParticle.hpp"
#include "src/images/PngImage.hpp"

namespace Objects
{
    class EvolutionParticleGenerator
    {
    public:
        static std::vector<EvolutionParticlePtr>* GenerateFlyArounds(LoaderPtr loader, std::function<void(void)> callback);
        static std::vector<EvolutionParticlePtr>* GenerateRain(LoaderPtr loader, std::function<void(void)> callback);
        static std::vector<EvolutionQuadPtr>* GenerateCircles(LoaderPtr, glm::vec2 pos, std::function<void(void)> callback);

    private:
        static void AddFlyAroundAnimation(EvolutionParticlePtr particle, PointCompound4 p1, PointCompound4 p2,
                                                     PointCompound4 p3);
        static void GenerateFlyAroundA1(std::vector<EvolutionParticlePtr> *particles, LoaderPtr loader, PngImagePtr firstImg,
                                        PngImagePtr secondImg, PngImagePtr thirdImg, float renderDelay);
        static void GenerateFlyAroundB1(std::vector<EvolutionParticlePtr> *particles, LoaderPtr loader, PngImagePtr firstImg,
                                        PngImagePtr secondImg, PngImagePtr thirdImg, float renderDelay);
        static void GenerateFlyAroundA2(std::vector<EvolutionParticlePtr> *particles, LoaderPtr loader, PngImagePtr firstImg,
                                        PngImagePtr secondImg, PngImagePtr thirdImg, float renderDelay);
        static void GenerateFlyAroundB2(std::vector<EvolutionParticlePtr> *particles, LoaderPtr loader, PngImagePtr firstImg,
                                        PngImagePtr secondImg, PngImagePtr thirdImg, float renderDelay);
        static void GenerateRain(std::vector<EvolutionParticlePtr> *particles, LoaderPtr loader, PngImagePtr firstImg,
                                 float renderDelay, unsigned int rainLine);
        static void AddRainAnimation(EvolutionParticlePtr particle, PointCompound4 p1);
        static void GenerateCircle(std::vector<EvolutionQuadPtr> *particles, LoaderPtr loader, PngImagePtr firstImg,
                                   float renderDelay, glm::vec2 pos);
//        static void
        static EvolutionParticlePtr GenerateParticle(LoaderPtr loader, PngImagePtr firstImg, float renderDelay);
        static EvolutionParticlePtr GenerateParticle(LoaderPtr loader, PngImagePtr firstImg, PngImagePtr secondImg,
                                                     PngImagePtr thirdImg, float renderDelay);
    };
}

#endif //POKEMON_CUSTOM_EVOLUTION_EVOLUTIONPARTICLEGENERATOR_HPP
