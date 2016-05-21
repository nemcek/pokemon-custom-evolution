//
// Created by martin on 18.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_MANIPULATIONS_HPP
#define POKEMON_CUSTOM_EVOLUTION_MANIPULATIONS_HPP

#include <images/Image.hpp>
#include <images/BitMap.hpp>

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
};

#endif //POKEMON_CUSTOM_EVOLUTION_MANIPULATIONS_HPP
