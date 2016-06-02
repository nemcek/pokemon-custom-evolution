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
    ~TextAnimation();
    AnimationStatus Animate(float delta) override ;
};

typedef std::shared_ptr<TextAnimation> TextAnimationPtr;

#endif //POKEMON_CUSTOM_EVOLUTION_TEXTANIMATION_HPP
