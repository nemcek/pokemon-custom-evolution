//
// Created by martin on 23.05.2016.
//

#include "src/shaders/TextShader.hpp"

TextShader::TextShader() : ShaderProgram("src/shaders/vert_text.glsl", "src/shaders/frag_text.glsl")
{
    GetAllUniformLocations();
}

void TextShader::GetAllUniformLocations()
{
    this->projection = this->GetUniformLocation("projection");
    this->color = this->GetUniformLocation("textColor");
}

void TextShader::LoadProjection(glm::mat4 projection)
{
    this->LoadMatrix(this->projection, projection);
}

void TextShader::LoadTextColor(glm::vec3 color)
{
    this->LoadVector(this->color, color);
}
