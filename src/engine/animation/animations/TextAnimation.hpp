//
// Created by martin on 29.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_TEXTANIMATION_HPP
#define POKEMON_CUSTOM_EVOLUTION_TEXTANIMATION_HPP

#include "Animation.hpp"

class TextAnimation : public Animation
{
public:
    std::string text;

    TextAnimation();
    TextAnimation(bool repeat);
    bool Animate(float delta) override ;
};

#endif //POKEMON_CUSTOM_EVOLUTION_TEXTANIMATION_HPP
