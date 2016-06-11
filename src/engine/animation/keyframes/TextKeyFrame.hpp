//
// Created by martin on 29.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_TEXTKEYFRAME_HPP
#define POKEMON_CUSTOM_EVOLUTION_TEXTKEYFRAME_HPP

#include <string>
#include "KeyFrame.hpp"

namespace Engine
{
    namespace nsAnimation
    {
        namespace KeyFrames
        {
            class TextKeyFrame : public KeyFrame
            {
            public:
                std::string text;

                TextKeyFrame(float time, glm::vec2 pos, float scale, std::string text);
                TextKeyFrame(float time, glm::vec2 pos, float scale, std::string text,
                             std::function<void(void)> callback);
                ~TextKeyFrame();
            };

            typedef std::shared_ptr<TextKeyFrame> TextKeyFramePtr;
        }
    }
}
#endif //POKEMON_CUSTOM_EVOLUTION_TEXTKEYFRAME_HPP
