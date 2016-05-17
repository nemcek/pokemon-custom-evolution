//
// Created by martin on 17.05.2016.
//

#include "src/images/Image.hpp"

Image::Image() { }

Image::Image(std::vector<Pixel> *buffer, int width, int height) : buffer(buffer)
{
    this->width = width;
    this->height = height;
}
