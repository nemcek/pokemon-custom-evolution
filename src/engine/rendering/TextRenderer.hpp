//
// Created by martin on 23.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_TEXTRENDERER_HPP
#define POKEMON_CUSTOM_EVOLUTION_TEXTRENDERER_HPP

#include <shaders/TextShader.hpp>
#include <engine/text/Text.hpp>

class TextRenderer
{
private:
    GLuint _vao;
    GLuint _vbo;

    void Initialize();

public:
    TextShaderPtr shader;

    TextRenderer(TextShaderPtr shader);
    ~TextRenderer();
    void Render(TextPtr text, glm::mat4 projection);
    void Render(std::vector<TextPtr> text, glm::mat4 projection);
};

typedef std::shared_ptr<TextRenderer> TextRendererPtr;

#endif //POKEMON_CUSTOM_EVOLUTION_TEXTRENDERER_HPP
