//
// Created by martin on 31.05.2016.
//

#include "KeyFrame.hpp"
#include "images/BitMap.hpp"

#ifndef POKEMON_CUSTOM_EVOLUTION_EVOLUTIONKEYFRAME_HPP
#define POKEMON_CUSTOM_EVOLUTION_EVOLUTIONKEYFRAME_HPP

using namespace Images;

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
                unsigned int yColorOffset;
                bool changeToWhite;
                BitMapPtr fadeBitMap = nullptr;
                std::vector<BitMapPtr> *cachedBitMaps = nullptr;

                EvolutionKeyFrame(float time, glm::vec2 pos, float scale, bool swap = false);
                EvolutionKeyFrame(float time, glm::vec2 pos, float scale, std::function<void(void)> callback, bool swap = false);
                EvolutionKeyFrame(float time, glm::vec2 pos, float scale, glm::vec3 color, unsigned int yColorOffset,
                                  bool swap = false, bool changeToWhite = false);
                EvolutionKeyFrame(float time, glm::vec2 pos, float scale, BitMapPtr fadeBitMap, unsigned int yColorOffset,
                                  bool swap = false, bool changeToWhite = false);
                EvolutionKeyFrame(float time, glm::vec2 pos, float scale, std::vector<BitMapPtr> &cachedfadeBitMaps,
                                  bool swap = false, bool changeToWhite = false);
                EvolutionKeyFrame(float time, glm::vec2 pos, float scale, glm::vec3 color, unsigned int yColorOffset,
                                  std::function<void(void)> callback, bool swap = false);
                virtual ~EvolutionKeyFrame();
            };

            typedef std::shared_ptr<EvolutionKeyFrame> EvolutionKeyFramePtr;
        }
    }
}
#endif //POKEMON_CUSTOM_EVOLUTION_EVOLUTIONKEYFRAME_HPP
