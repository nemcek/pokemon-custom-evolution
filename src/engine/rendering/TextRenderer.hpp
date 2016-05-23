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
    GLuint vao;
    GLuint vbo;

    void Initialize();

public:
    TextShader *shader;

    TextRenderer(TextShader *shader);
    void Render(Text *text, glm::mat4 projection);
    void Render(std::vector<Text *> text, glm::mat4 projection);
};

#endif //POKEMON_CUSTOM_EVOLUTION_TEXTRENDERER_HPP
