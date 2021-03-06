//
// Created by martin on 23.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_TEXTSHADER_HPP
#define POKEMON_CUSTOM_EVOLUTION_TEXTSHADER_HPP

#include "ShaderProgram.hpp"

namespace Shaders
{
    class TextShader : public ShaderProgram
    {
    private:
        GLint _projection;
        GLint _color;

    public:
        TextShader();
        ~TextShader();
        void GetAllUniformLocations() override;
        void LoadProjection(glm::mat4 projection);
        void LoadTextColor(glm::vec3 color);
    };

    typedef std::shared_ptr<TextShader> TextShaderPtr;
}
#endif //POKEMON_CUSTOM_EVOLUTION_TEXTSHADER_HPP
