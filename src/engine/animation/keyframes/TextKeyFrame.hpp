//
// Created by martin on 29.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_TEXTKEYFRAME_HPP
#define POKEMON_CUSTOM_EVOLUTION_TEXTKEYFRAME_HPP

#include <string>
#include "KeyFrame.hpp"

class TextKeyFrame : public KeyFrame
{
public:
    std::string text;

    TextKeyFrame(float time, glm::vec2 pos, float scale, std::string text);
    TextKeyFrame(float time, glm::vec2 pos, float scale, std::string text, std::function<void (void)> callback);
};


#endif //POKEMON_CUSTOM_EVOLUTION_TEXTKEYFRAME_HPP
