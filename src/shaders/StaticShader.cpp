//
// Created by martin on 23.05.2016.
//

#include "src/shaders/StaticShader.hpp"

StaticShader::StaticShader() : ShaderProgram("src/shaders/vert_texture.glsl", "src/shaders/frag_texture.glsl")
{
    GetAllUniformLocations();
}

void StaticShader::GetAllUniformLocations()
{
    this->texture = GetUniformLocation("Texture");
    this->position = GetUniformLocation("quadPos");
}

void StaticShader::LoadTexture(unsigned int textureId)
{
    ShaderProgram::LoadTexture(this->texture, textureId);
}

void StaticShader::LoadPosition(glm::vec2 position)
{
    this->LoadVector(this->position, position);
}