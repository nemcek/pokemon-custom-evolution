//
// Created by martin on 17.05.2016.
//

#include "src/images/Image.hpp"

Image::Image() { }

Image::Image(std::vector<Pixel> *buffer, int width, int height, int bit_depth, IMAGE_COLOR_TYPE color_type) : buffer(buffer)
{
    this->width = width;
    this->height = height;
    this->bit_depth = bit_depth;
    this->color_type = color_type;
}

std::vector<Pixel>* Image::ChangeToWhite()
{
    std::vector<Pixel> *framebuffer = new std::vector<Pixel>((unsigned long) (this->width * this->height));

    for (int y = 0; y < this->height; y++)
    {
        for (int x = 0; x < this->width; x++)
        {
            if ((*this->buffer)[y * this->width + x].A == 0)
                (*framebuffer)[y * this->width + x] = (*this->buffer)[y * this->width + x];
            else
            {
                (*framebuffer)[y * this->width + x].R = 255;
                (*framebuffer)[y * this->width + x].G = 255;
                (*framebuffer)[y * this->width + x].B = 255;
            }
        }
    }

    return framebuffer;
}
