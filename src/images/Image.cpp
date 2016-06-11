//
// Created by martin on 17.05.2016.
//

#include "src/images/Image.hpp"

namespace Images
{
    Image::Image() { }

    Image::Image(BitMapPtr bitmap, int bit_depth, IMAGE_COLOR_TYPE color_type) : bitmap(bitmap) {
        this->bitDepth = bit_depth;
        this->colorType = color_type;
    }

    Image::~Image() { }
}