//
// Created by martin on 24.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_RAWMODEL_HPP
#define POKEMON_CUSTOM_EVOLUTION_RAWMODEL_HPP

#include <GL/glew.h>

class RawModel
{
public:
    GLuint vao;
    GLuint vbo;
    GLuint tbo;

    RawModel();
};

#endif //POKEMON_CUSTOM_EVOLUTION_RAWMODEL_HPP
