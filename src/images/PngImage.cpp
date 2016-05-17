//
// Created by martin on 17.05.2016.
//

#include "src/images/PngImage.hpp"

PngImage::PngImage(const char *file_name)
{
    png_image_t *png_image = new png_image_t();
    ImageLoader::LoadPNGImage(file_name, png_image);

    this->width = png_image->width;
    this->height = png_image->height;
    this->bit_depth = png_image->bit_depth;
    this->color_type = png_image->color_type;

    CreateBuffer(png_image->row_pointers);
}

bool PngImage::CreateBuffer(png_bytep *row_pointers)
{
    std::vector<Pixel> *framebuffer = new std::vector<Pixel>((unsigned long) (this->width * this->height));

    for (int y = 0; y < this->height; y++)
    {
        png_byte* row = row_pointers[y];

        for (int x = 0; x < this->width; x++) {
            png_byte* ptr = &(row[x*4]);
            (*framebuffer)[y * this->width + x] = { ptr[0], ptr[1], ptr[2], ptr[3] };
        }
    }

    this->buffer = framebuffer;

    return true;
}

