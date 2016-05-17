//
// Created by martin on 17.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_PNGIMAGE_HPP
#define POKEMON_CUSTOM_EVOLUTION_PNGIMAGE_HPP

#include <memory>
#include "Image.hpp"

class PngImage : Image
{
public:
    PngImage(png_byte *buffer, int width, int height);
};

typedef std::shared_ptr<PngImage> PngImagePtr;

#endif //POKEMON_CUSTOM_EVOLUTION_PNGIMAGE_HPP
