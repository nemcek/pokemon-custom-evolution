//
// Created by martin on 24.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_LOADER_HPP
#define POKEMON_CUSTOM_EVOLUTION_LOADER_HPP

#include <GL/glew.h>
#include <objects/RawModel.hpp>
#include <vector>
#include <images/BitMap.hpp>

class Loader
{
private:
    GLuint programId;

public:
    Loader(GLuint programId);
    RawModel *Load(std::vector<GLfloat> vertex_buffer, std::vector<GLfloat> textcoord_buffer);
    GLuint LoadTexture(BitMap *bitMap);
    void LoadVertexBuffer(GLuint location, std::vector<GLfloat> vertex_buffer);
};

#endif //POKEMON_CUSTOM_EVOLUTION_LOADER_HPP
