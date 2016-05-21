//
// Created by martin on 20.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_BITMAP_HPP
#define POKEMON_CUSTOM_EVOLUTION_BITMAP_HPP

#include <vector>

struct Pixel
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
    unsigned char A;
};

/*
 * Wrapper class
 */
class BitMap
{
private:
    Pixel default_value = { 0, 0, 0, 0 };

public:
    BitMap(int width, int height);

    std::vector<Pixel> *buffer;
    int width;
    int height;
};

#endif //POKEMON_CUSTOM_EVOLUTION_BITMAP_HPP
