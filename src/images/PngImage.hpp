//
// Created by martin on 17.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_PNGIMAGE_HPP
#define POKEMON_CUSTOM_EVOLUTION_PNGIMAGE_HPP

#include <memory>
#include "Image.hpp"

namespace Images
{
    class PngImage : public Image
    {
    private:
        bool CreateBitMap(png_bytep *row_pointers, int width, int height);

    public:
        PngImage(const char *file_name);
        ~PngImage();
    };

    typedef std::shared_ptr<PngImage> PngImagePtr;
}
#endif //POKEMON_CUSTOM_EVOLUTION_PNGIMAGE_HPP
