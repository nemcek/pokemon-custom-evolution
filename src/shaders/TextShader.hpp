//
// Created by martin on 23.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_TEXTSHADER_HPP
#define POKEMON_CUSTOM_EVOLUTION_TEXTSHADER_HPP

#include "ShaderProgram.hpp"

class TextShader : public ShaderProgram
{
private:
    GLint projection;
    GLint color;

public:
    TextShader();

    void GetAllUniformLocations() override ;
    void LoadProjection(glm::mat4 projection);
    void LoadTextColor(glm::vec3 color);
};

#endif //POKEMON_CUSTOM_EVOLUTION_TEXTSHADER_HPP