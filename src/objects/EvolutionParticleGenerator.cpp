//
// Created by martin on 14.06.2016.
//

#include <images/PngImage.hpp>
#include <constants/Constants.hpp>
#include "EvolutionParticleGenerator.hpp"

namespace Objects
{
    std::vector<EvolutionParticlePtr>* EvolutionParticleGenerator::GenerateFlyArounds(LoaderPtr loader, std::function<void(void)> callback) {
        int particlesCount = 10;
        float particleDelayMs = .1f;
        float totalParticlesDelay = 0.0f;

        std::vector<EvolutionParticlePtr> *particles = new std::vector<EvolutionParticlePtr>;

        PngImagePtr particleCircleImage = std::make_shared<PngImage>("data/evolution_particle_circle.png");
        PngImagePtr particleCrossImage = std::make_shared<PngImage>("data/evolution_particle_cross.png");
        PngImagePtr particleQuadImage = std::make_shared<PngImage>("data/evolution_particle_quad.png");

        for (int i = 0; i < particlesCount; i++, totalParticlesDelay += particleDelayMs) {
            GenerateFlyAroundA1(particles, loader, particleCircleImage, particleQuadImage, particleCrossImage, totalParticlesDelay);
            GenerateFlyAroundB1(particles, loader, particleCircleImage, particleQuadImage, particleCrossImage, totalParticlesDelay);
            GenerateFlyAroundA2(particles, loader, particleCircleImage, particleQuadImage, particleCrossImage, totalParticlesDelay);
            GenerateFlyAroundB2(particles, loader, particleCircleImage, particleQuadImage, particleCrossImage, totalParticlesDelay);
        }

        particles[0][particles->size() - 1]->animation->GetLastKetFrame()->callback = callback;
        return particles;
    }

    std::vector<EvolutionParticlePtr>* EvolutionParticleGenerator::GenerateRain(LoaderPtr loader, std::function<void(void)> callback) {
        int particlesCount = 6;
        int rainLinesCount = 10;
        float particleDelayMs = .03f;
        float totalParticlesDelay = 0.0f;

        std::vector<EvolutionParticlePtr> *particles = new std::vector<EvolutionParticlePtr>;
        PngImagePtr particleQuadImage = std::make_shared<PngImage>("data/evolution_particle_quad.png");

        for (unsigned int j = 0; j < particlesCount; j++, totalParticlesDelay += particleDelayMs) {
            for (unsigned int i = 0; i < rainLinesCount; i++) {
                GenerateRain(particles, loader, particleQuadImage, totalParticlesDelay, i);
            }
        }

        particles[0][particles->size() - 1]->animation->GetLastKetFrame()->callback = callback;
        return particles;
    }

    std::vector<EvolutionQuadPtr>* EvolutionParticleGenerator::GenerateCircles(LoaderPtr loader, glm::vec2 pos,  std::function<void(
            void)> callback) {
        unsigned int circlesCount = 2;
        float circleDelay = 1.1f;
        float totalCircleDelay = 0.0f;

        PngImagePtr img = std::make_shared<PngImage>("data/evolution_circle.png");
        std::vector<EvolutionQuadPtr> *particles = new std::vector<EvolutionQuadPtr>;

        for (unsigned int i = 0; i < circlesCount; i++, totalCircleDelay += circleDelay) {
            GenerateCircle(particles, loader, img, totalCircleDelay, pos);
        }

        return particles;
    }

    void EvolutionParticleGenerator::AddFlyAroundAnimation(EvolutionParticlePtr particle, PointCompound4 p1,
                                                                      PointCompound4 p2, PointCompound4 p3) {
        particle->animation = std::make_shared<ParticleAnimation>(particle->bitMap);
        particle->animation->enabled = true;
        particle->animation->repeat = false;
        particle->animation->Add(std::make_shared<ParticleKeyFrame>(0.0f, particle->position, 1.0f,
                                                                    p1));
        particle->animation->Add(std::make_shared<ParticleKeyFrame>(.83f, particle->position, .8f,
                                                                    p2, true));
        particle->animation->Add(std::make_shared<ParticleKeyFrame>(1.66f, particle->position, .6f,
                                                                    p3, true));
        particle->animation->Add(std::make_shared<ParticleKeyFrame>(2.0f, particle->position, .0f,
                                                                    p3, true));
    }

    void EvolutionParticleGenerator::GenerateFlyAroundA1(std::vector<EvolutionParticlePtr> *particles, LoaderPtr loader,
                                                         PngImagePtr firstImg, PngImagePtr secondImg,
                                                         PngImagePtr thirdImg, float renderDelay) {
        EvolutionParticlePtr particle = GenerateParticle(loader, firstImg, secondImg, thirdImg, renderDelay);
        PointCompound4 pointCompound = {{74, 467}, {115, 522}, {681, 679}, {797, 623}};
        PointCompound4 pointCompound2 = {{797, 618}, {624, 607}, {81, 647}, {238, 799}};
        PointCompound4 pointCompound3 = {{238, 799}, {361, 863}, {391, 888}, {398, 958}};

        AddFlyAroundAnimation(particle, pointCompound, pointCompound2, pointCompound3);

        particles->push_back(particle);
    }

    void EvolutionParticleGenerator::GenerateFlyAroundB1(std::vector<EvolutionParticlePtr> *particles, LoaderPtr loader,
                                                         PngImagePtr firstImg, PngImagePtr secondImg,
                                                         PngImagePtr thirdImg, float renderDelay) {
        EvolutionParticlePtr particle = GenerateParticle(loader, firstImg, secondImg, thirdImg, renderDelay);
        PointCompound4 pointCompound = {{287, 357}, {25, 391}, {24, 551}, {792, 668}};
        PointCompound4 pointCompound2 = {{792, 668}, {546, 641}, {268, 727}, {374, 839}};
        PointCompound4 pointCompound3 = {{374, 839}, {432, 883}, {431, 909}, {431, 956}};

        AddFlyAroundAnimation(particle, pointCompound, pointCompound2, pointCompound3);

        particles->push_back(particle);
    }

    void EvolutionParticleGenerator::GenerateFlyAroundA2(std::vector<EvolutionParticlePtr> *particles, LoaderPtr loader,
                                                         PngImagePtr firstImg, PngImagePtr secondImg,
                                                         PngImagePtr thirdImg, float renderDelay) {
        EvolutionParticlePtr particle = GenerateParticle(loader, firstImg, secondImg, thirdImg, renderDelay);
        PointCompound4 pointCompound = {{786, 519}, {955, 257}, {117, 469}, {186, 643}};
        PointCompound4 pointCompound2 = {{186, 643}, {145, 725}, {472, 809}, {503, 863}};
        PointCompound4 pointCompound3 = {{503, 863}, {537, 910}, {537, 918}, {537, 956}};

        AddFlyAroundAnimation(particle, pointCompound, pointCompound2, pointCompound3);

        particles->push_back(particle);
    }

    void EvolutionParticleGenerator::GenerateFlyAroundB2(std::vector<EvolutionParticlePtr> *particles, LoaderPtr loader,
                                                         PngImagePtr firstImg, PngImagePtr secondImg,
                                                         PngImagePtr thirdImg, float renderDelay) {
        EvolutionParticlePtr particle = GenerateParticle(loader, firstImg, secondImg, thirdImg, renderDelay);
        PointCompound4 pointCompound = {{884, 395}, {676, 299}, {2, 394}, {177, 573}};
        PointCompound4 pointCompound2 = {{177, 573}, {332, 705}, {545, 785}, {691, 801}};
        PointCompound4 pointCompound3 = {{691, 801}, {534, 854}, {515, 922}, {514, 957}};

        AddFlyAroundAnimation(particle, pointCompound, pointCompound2, pointCompound3);

        particles->push_back(particle);
    }

    void EvolutionParticleGenerator::GenerateRain(std::vector<EvolutionParticlePtr> *particles, LoaderPtr loader,
                                                  PngImagePtr firstImg, float renderDelay, unsigned int rainLine) {
        EvolutionParticlePtr particle = GenerateParticle(loader, firstImg, renderDelay);
        PointCompound4 pointCompound = {{475, 950},
                                        {250 + (rainLine * 56), 922},
                                        {-20 + (rainLine * 118), 621},
                                        {100 + (rainLine * 88), 354}};

        AddRainAnimation(particle, pointCompound);

        particles->push_back(particle);
    }

    void EvolutionParticleGenerator::AddRainAnimation(EvolutionParticlePtr particle, PointCompound4 p1) {
        PointCompound4 p = {{-100, -100}, {-100, -100}, {-100, -100}, {-100, -100}};
        particle->animation = std::make_shared<ParticleAnimation>(particle->bitMap);
        particle->animation->enabled = true;
        particle->animation->repeat = false;
        particle->animation->Add(std::make_shared<ParticleKeyFrame>(0.0f, particle->position, .4f, p1));
        particle->animation->Add(std::make_shared<ParticleKeyFrame>(.5f, particle->position, .4f, p1));
        particle->animation->Add(std::make_shared<ParticleKeyFrame>(.5f, glm::vec2(-10.0f, -10.0f), .0f, p));
    }


    void EvolutionParticleGenerator::GenerateCircle(std::vector<EvolutionQuadPtr> *particles, LoaderPtr loader,
                                                    PngImagePtr firstImg, float renderDelay, glm::vec2 pos) {
        EvolutionQuadPtr particle;
        particle = std::make_shared<EvolutionQuad>(loader, pos, 1.0f, firstImg->bitmap, nullptr);

        particle->renderDelay = renderDelay;
        particle->animation = std::make_shared<EvolutionAnimation>(particle->bitMap);
        particle->animation->enabled = true;
        particle->animation->repeat = false;
        particle->animation->Add(std::make_shared<EvolutionKeyFrame>(0.0f, particle->position, particle->scaleX));
        particle->animation->Add(std::make_shared<EvolutionKeyFrame>(1.5f, particle->position, 0.0f));

        particles->push_back(particle);
    }

    EvolutionParticlePtr EvolutionParticleGenerator::GenerateParticle(LoaderPtr loader, PngImagePtr firstImg,
                                                                      float renderDelay) {
        EvolutionParticlePtr particle = std::make_shared<EvolutionParticle>(loader,
                                                                            glm::vec2(Constants::WINDOW_WIDTH / 2,
                                                                                      Constants::WINDOW_HEIGHT / 2),
                                                                            0.05f,
                                                                            firstImg->bitmap,
                                                                            renderDelay);

        return particle;
    }

    EvolutionParticlePtr EvolutionParticleGenerator::GenerateParticle(LoaderPtr loader, PngImagePtr firstImg,
                                                                      PngImagePtr secondImg, PngImagePtr thirdImg,
                                                                      float renderDelay) {
        EvolutionParticlePtr particle = std::make_shared<EvolutionParticle>(loader,
                                                                            glm::vec2(Constants::WINDOW_WIDTH / 2,
                                                                                      Constants::WINDOW_HEIGHT / 2),
                                                                            0.05f,
                                                                            firstImg->bitmap,
                                                                            secondImg->bitmap,
                                                                            thirdImg->bitmap,
                                                                            renderDelay);

        return particle;
    }
}