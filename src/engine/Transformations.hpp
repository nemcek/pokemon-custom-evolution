//
// Created by martin on 18.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_MANIPULATIONS_HPP
#define POKEMON_CUSTOM_EVOLUTION_MANIPULATIONS_HPP

#include <images/Image.hpp>
#include <images/BitMap.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

enum PicturePosition
{
    Center
};

class Transformations
{
private:
    static const BitMapPtr &Center(const BitMapPtr &background, const BitMapPtr &foreground);

public:
    static const BitMapPtr &Scale(const BitMapPtr &bitmap, int new_width, int new_height);
    static BitMapPtr &ChangeToWhite(BitMapPtr &bitmap);
    static const BitMapPtr &Concat(const BitMapPtr &background, const BitMapPtr &foreground, PicturePosition position);
    static glm::vec2 ToOpenGLCoords(glm::vec2 position, int window_width, int window_height);
    static glm::vec2 Lerp(glm::vec2 a, glm::vec2 b, float t);
    static float Lerp(float a, float b, float t);
    static const BitMapPtr &Fade(const BitMapPtr &background, glm::vec3 fadeColor, unsigned int yOffset, float fadeTime);
};

#endif //POKEMON_CUSTOM_EVOLUTION_MANIPULATIONS_HPP
