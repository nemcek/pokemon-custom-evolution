//
// Created by martin on 20.05.2016.
//

#include "src/images/BitMap.hpp"

BitMap::BitMap(int width, int height)
{
    this->width = width;
    this->height = height;
    this->buffer = std::vector<Pixel> ((unsigned long)(width * height), _defaultValue);
}

BitMap::~BitMap()
{
    buffer.clear();
}
