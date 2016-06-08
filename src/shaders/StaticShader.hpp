//
// Created by martin on 23.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_STATICSHADER_HPP
#define POKEMON_CUSTOM_EVOLUTION_STATICSHADER_HPP

#include "ShaderProgram.hpp"

class StaticShader : public ShaderProgram
{
private:
    GLint _texture;
    GLint _position;

public:
    StaticShader();
    ~StaticShader();
    void GetAllUniformLocations() override ;
    void LoadTexture(unsigned int textureId) const;
    void LoadPosition(glm::vec2 position) const;
};

typedef std::shared_ptr<StaticShader> StaticShaderPtr;

#endif //POKEMON_CUSTOM_EVOLUTION_STATICSHADER_HPP
