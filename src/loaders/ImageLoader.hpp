//
// Created by Martin on 14. 5. 2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_IMAGELOADER_HPP
#define POKEMON_CUSTOM_EVOLUTION_IMAGELOADER_HPP

#include <GL/glew.h>
#include <png.h>
#include <stdlib.h>
#include <memory>

namespace Loaders
{
    enum IMAGE_COLOR_TYPE {
        RGB,
        RGBA
    };

    struct png_image_t {
        png_bytep *row_pointers;
        int width;
        int height;
        int bit_depth;
        IMAGE_COLOR_TYPE color_type;

        ~png_image_t() { free(row_pointers); }
    };

    class ImageLoader
    {
    public:
        static bool LoadPNGImage(const char *, png_image_t *);
    };

    typedef std::shared_ptr<ImageLoader> ImageLoaderPtr;
}
#endif //POKEMON_CUSTOM_EVOLUTION_IMAGELOADER_HPP
