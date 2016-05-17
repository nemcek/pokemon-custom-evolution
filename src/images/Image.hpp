//
// Created by martin on 17.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_IMAGE_HPP
#define POKEMON_CUSTOM_EVOLUTION_IMAGE_HPP

#include <vector>
#include <png.h>
#include <memory>

struct Pixel
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
    unsigned char A;
};

class Image
{
public:
    Image();
    Image(std::vector<Pixel> *buffer, int width, int height);

    std::vector<Pixel> *buffer;
    int width;
    int height;
};

typedef std::shared_ptr<Image> ImagePtr;

#endif //POKEMON_CUSTOM_EVOLUTION_IMAGE_HPP
