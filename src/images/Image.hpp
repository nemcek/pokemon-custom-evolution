//
// Created by martin on 17.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_IMAGE_HPP
#define POKEMON_CUSTOM_EVOLUTION_IMAGE_HPP

#include <png.h>
#include <vector>
#include <memory>
#include "src/loaders/ImageLoader.hpp"
#include "src/images/BitMap.hpp"

class Image
{
public:
    Image();
    Image(BitMap *bitmap, int bit_depth, IMAGE_COLOR_TYPE color_type);
    ~Image();

    BitMap *bitmap;
    int bitDepth;
    IMAGE_COLOR_TYPE colorType;
};

typedef std::shared_ptr<Image> ImagePtr;

#endif //POKEMON_CUSTOM_EVOLUTION_IMAGE_HPP
