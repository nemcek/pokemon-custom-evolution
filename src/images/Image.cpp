//
// Created by martin on 17.05.2016.
//

#include "src/images/Image.hpp"

Image::Image() { }

Image::Image(BitMap *bitmap, int bit_depth, IMAGE_COLOR_TYPE color_type) : bitmap(bitmap)
{
    this->bit_depth = bit_depth;
    this->color_type = color_type;
}


