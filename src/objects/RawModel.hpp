//
// Created by martin on 24.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_RAWMODEL_HPP
#define POKEMON_CUSTOM_EVOLUTION_RAWMODEL_HPP

#include <GL/glew.h>
#include <memory>

class RawModel
{
public:
    GLuint vao;
    GLuint vbo;
    GLuint tbo;

    RawModel();
    ~RawModel();
};

typedef std::shared_ptr<RawModel> RawModelPtr;

#endif //POKEMON_CUSTOM_EVOLUTION_RAWMODEL_HPP
