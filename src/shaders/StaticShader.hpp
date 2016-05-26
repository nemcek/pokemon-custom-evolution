//
// Created by martin on 23.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_STATICSHADER_HPP
#define POKEMON_CUSTOM_EVOLUTION_STATICSHADER_HPP

#include "ShaderProgram.hpp"

class StaticShader : public ShaderProgram
{
private:
    GLint texture;
    GLint position;

public:
    StaticShader();
    void GetAllUniformLocations() override ;
    void LoadTexture(unsigned int textureId);
    void LoadPosition(glm::vec2 position);
};

#endif //POKEMON_CUSTOM_EVOLUTION_STATICSHADER_HPP
