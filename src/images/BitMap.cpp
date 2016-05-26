//
// Created by martin on 20.05.2016.
//

#include "src/images/BitMap.hpp"

BitMap::BitMap(int width, int height)
{
    this->width = width;
    this->height = height;
    this->buffer = new std::vector<Pixel> ((unsigned long)(width * height), { 0, 0, 0, 0 });
}