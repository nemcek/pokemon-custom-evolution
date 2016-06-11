//
// Created by martin on 31.05.2016.
//

#include "KeyFrame.hpp"

#ifndef POKEMON_CUSTOM_EVOLUTION_EVOLUTIONKEYFRAME_HPP
#define POKEMON_CUSTOM_EVOLUTION_EVOLUTIONKEYFRAME_HPP

namespace Engine
{
    namespace nsAnimation
    {
        namespace KeyFrames
        {
            class EvolutionKeyFrame : public KeyFrame
            {
            public:
                bool swap = false;
                glm::vec3 color;
                bool colorEnabled = false;

                EvolutionKeyFrame(float time, glm::vec2 pos, float scale, bool swap = false);
                EvolutionKeyFrame(float time, glm::vec2 pos, float scale, glm::vec3 color, bool swap = false);
                EvolutionKeyFrame(float time, glm::vec2 pos, float scale, glm::vec3 color,
                                  std::function<void(void)> callback, bool swap = false);
                virtual ~EvolutionKeyFrame();
            };

            typedef std::shared_ptr<EvolutionKeyFrame> EvolutionKeyFramePtr;
        }
    }
}
#endif //POKEMON_CUSTOM_EVOLUTION_EVOLUTIONKEYFRAME_HPP
