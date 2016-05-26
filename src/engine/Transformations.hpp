//
// Created by martin on 18.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_MANIPULATIONS_HPP
#define POKEMON_CUSTOM_EVOLUTION_MANIPULATIONS_HPP

#include <images/Image.hpp>
#include <images/BitMap.hpp>
#include <glm/vec2.hpp>

enum PicturePosition
{
    Center
};

class Transformations
{
private:
    static BitMap *Center(BitMap *background, BitMap *foreground);

public:
    static BitMap *Scale(BitMap *bitmap, int new_width, int new_height);
    static BitMap *ChangeToWhite(BitMap *bitmap);
    static BitMap *Concat(BitMap *background, BitMap *foreground, PicturePosition position);
    static glm::vec2 ToOpenGLCoords(glm::vec2 position, int window_width, int window_height);
    static glm::vec2 Lerp(glm::vec2 a, glm::vec2 b, float t);
    static float Lerp(float a, float b, float t);
};

#endif //POKEMON_CUSTOM_EVOLUTION_MANIPULATIONS_HPP
