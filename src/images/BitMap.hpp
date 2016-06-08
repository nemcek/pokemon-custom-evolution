//
// Created by martin on 20.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_BITMAP_HPP
#define POKEMON_CUSTOM_EVOLUTION_BITMAP_HPP

#include <vector>
#include <memory>

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
    Pixel _defaultValue = { 0, 0, 0, 0 };

public:
    std::vector<Pixel> buffer;
    int width;
    int height;

    BitMap(int width, int height);
    ~BitMap();
};

typedef std::shared_ptr<BitMap> BitMapPtr;

#endif //POKEMON_CUSTOM_EVOLUTION_BITMAP_HPP
