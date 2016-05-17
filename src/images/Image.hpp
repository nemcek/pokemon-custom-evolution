//
// Created by martin on 17.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_IMAGE_HPP
#define POKEMON_CUSTOM_EVOLUTION_IMAGE_HPP

#include <vector>
#include <png.h>
#include <memory>
#include "src/loaders/ImageLoader.hpp"

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
    Image(std::vector<Pixel> *buffer, int width, int height, int bit_depth, IMAGE_COLOR_TYPE color_type);
    std::vector<Pixel> *ChangeToWhite();

    std::vector<Pixel> *buffer;
    int width;
    int height;
    int bit_depth;
    IMAGE_COLOR_TYPE color_type;
};

typedef std::shared_ptr<Image> ImagePtr;

#endif //POKEMON_CUSTOM_EVOLUTION_IMAGE_HPP
