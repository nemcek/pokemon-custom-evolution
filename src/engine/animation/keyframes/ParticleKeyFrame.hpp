//
// Created by martin on 12.06.2016.
//

#include <engine/Transformations.hpp>
#include "EvolutionKeyFrame.hpp"

#ifndef POKEMON_CUSTOM_EVOLUTION_PARTICLEKEYFRAME_HPP
#define POKEMON_CUSTOM_EVOLUTION_PARTICLEKEYFRAME_HPP

namespace Engine
{
    namespace nsAnimation
    {
        namespace KeyFrames
        {
            struct PointCompound4
            {
                Point A;
                Point B;
                Point C;
                Point D;
            };
            class ParticleKeyFrame : public EvolutionKeyFrame
            {
            public:
                PointCompound4 pointCompound;
                ParticleKeyFrame(float time, glm::vec2 pos, float scale, PointCompound4 pointCompound, bool swap = false);
                ~ParticleKeyFrame();
            };

            typedef std::shared_ptr<ParticleKeyFrame> ParticleKeyFramePtr;
        }
    }
}

#endif //POKEMON_CUSTOM_EVOLUTION_PARTICLEKEYFRAME_HPP
