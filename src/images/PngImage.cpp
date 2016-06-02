//
// Created by martin on 17.05.2016.
//

#include "src/images/PngImage.hpp"

PngImage::PngImage(const char *file_name)
{
    png_image_t *png_image = new png_image_t();
    ImageLoader::LoadPNGImage(file_name, png_image);

    this->bitDepth = png_image->bit_depth;
    this->colorType = png_image->color_type;

    CreateBitMap(png_image->row_pointers, png_image->width, png_image->height);
}

PngImage::~PngImage()
{
}

bool PngImage::CreateBitMap(png_bytep *row_pointers, int width, int height)
{
    BitMapPtr bitmap = std::make_shared<BitMap>(width, height);

    for (int y = 0; y < height; y++)
    {
        png_byte* row = row_pointers[y];

        for (int x = 0; x < width; x++) {
            png_byte* ptr = &(row[x*4]);
            (*bitmap->buffer)[y * width + x] = { ptr[0], ptr[1], ptr[2], ptr[3] };
        }
    }

    this->bitmap = bitmap;

    return true;
}

