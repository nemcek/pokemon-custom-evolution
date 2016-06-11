//
// Created by martin on 12.06.2016.
//

#include "ParticleKeyFrame.hpp"

namespace Engine
{
    namespace  nsAnimation
    {
        namespace KeyFrames
        {
            ParticleKeyFrame::ParticleKeyFrame(float time, glm::vec2 pos, float scale, PointCompound4 pointCompound,
                                               bool swap)
                : EvolutionKeyFrame(time, pos, scale, swap)
                , pointCompound(pointCompound) {

            }
            ParticleKeyFrame::~ParticleKeyFrame() { }
        }
    }
}