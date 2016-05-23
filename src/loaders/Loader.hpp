//
// Created by Martin on 14. 5. 2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_LOADER_HPP
#define POKEMON_CUSTOM_EVOLUTION_LOADER_HPP

#include <GL/glew.h>
#include <string>
#include "src/images/Image.hpp"

class Loader
{
public:
    static GLuint LoadTexture(Image *image, GLuint program_id);
    static GLuint LoadDDS(const char *path);
};

typedef std::shared_ptr<Loader> LoaderPtr;

#endif //POKEMON_CUSTOM_EVOLUTION_LOADER_HPP
