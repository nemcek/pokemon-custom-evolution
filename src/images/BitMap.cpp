//
// Created by martin on 20.05.2016.
//

#include "src/images/BitMap.hpp"

namespace Images
{
    BitMap::BitMap(int width, int height) {
        this->width = width;
        this->height = height;
        this->buffer = new std::vector<Pixel>((unsigned long) (width * height), _defaultValue);
    }

    BitMap::~BitMap() {
        buffer->clear();
    }
}