//
// Created by martin on 23.05.2016.
//

#include "src/shaders/TextShader.hpp"

namespace Shaders
{
    TextShader::TextShader() : ShaderProgram("src/shaders/vert_text.glsl", "src/shaders/frag_text.glsl") {
        GetAllUniformLocations();
    }

    TextShader::~TextShader() { }

    void TextShader::GetAllUniformLocations() {
        this->_projection = this->GetUniformLocation("projection");
        this->_color = this->GetUniformLocation("textColor");
    }

    void TextShader::LoadProjection(glm::mat4 projection) {
        this->LoadMatrix(this->_projection, projection);
    }

    void TextShader::LoadTextColor(glm::vec3 color) {
        this->LoadVector(this->_color, color);
    }
}