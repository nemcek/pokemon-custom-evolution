//
// Created by martin on 14.06.2016.
//

#include <images/PngImage.hpp>
#include <constants/Constants.hpp>
#include "EvolutionParticleGenerator.hpp"

namespace Objects
{
    std::vector<EvolutionParticlePtr>* EvolutionParticleGenerator::GenerateFlyArounds(LoaderPtr loader) {
        int particlesCount = 10;
        float particleDelayMs = .1f;
        float totalParticlesDelay = 0.0f;

        std::vector<EvolutionParticlePtr> *particles = new std::vector<EvolutionParticlePtr>;

        PngImagePtr particleCircleImage = std::make_shared<PngImage>("data/evolution_particle_circle.png");
        PngImagePtr particleCrossImage = std::make_shared<PngImage>("data/evolution_particle_cross.png");
        PngImagePtr particleQuadImage = std::make_shared<PngImage>("data/evolution_particle_quad.png");

        for (int i = 0; i < particlesCount; i++, totalParticlesDelay += particleDelayMs) {
            EvolutionParticlePtr particleCircle = std::make_shared<EvolutionParticle>(loader,
                                                                                      glm::vec2(Constants::WINDOW_WIDTH / 2,
                                                                                                Constants::WINDOW_HEIGHT / 2),
                                                                                      0.05f,
                                                                                      particleCircleImage->bitmap,
                                                                                      particleQuadImage->bitmap,
                                                                                      particleCrossImage->bitmap,
                                                                                      totalParticlesDelay);

            PointCompound4 pointCompound = {{74, 467}, {115, 522}, {681, 679}, {797, 623}};
            PointCompound4 pointCompound2 = {{797, 618}, {624, 607}, {81, 647}, {238, 799}};
            PointCompound4 pointCompound3 = {{238, 799}, {361, 863}, {391, 888}, {398, 958}};

            particleCircle->animation = std::make_shared<ParticleAnimation>(particleCircle->bitMap);
            particleCircle->animation->enabled = true;
            particleCircle->animation->repeat = false;
            particleCircle->animation->Add(std::make_shared<ParticleKeyFrame>(0.0f, particleCircle->position, 1.0f,
                                                                              pointCompound));
            particleCircle->animation->Add(std::make_shared<ParticleKeyFrame>(1.0f, particleCircle->position, .8f,
                                                                              pointCompound2, true));
            particleCircle->animation->Add(std::make_shared<ParticleKeyFrame>(2.0f, particleCircle->position, .6f,
                                                                              pointCompound3, true));
            particleCircle->animation->Add(std::make_shared<ParticleKeyFrame>(2.33f, particleCircle->position, .0f,
                                                                              pointCompound3, true));

            particles->push_back(particleCircle);
        }

        return particles;
    }
}