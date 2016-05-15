//
// Created by Martin on 14. 5. 2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_IMAGELOADER_HPP
#define POKEMON_CUSTOM_EVOLUTION_IMAGELOADER_HPP

#include <GL/glew.h>
#include <png.h>
#include <stdlib.h>
#include <memory>

class ImageLoader {
public:
    static bool LoadPNGImage(const char *, png_byte *, int *, int* );
};

typedef std::shared_ptr<ImageLoader> ImageLoaderPtr;

#endif //POKEMON_CUSTOM_EVOLUTION_IMAGELOADER_HPP
