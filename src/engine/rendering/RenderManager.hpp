//
// Created by martin on 23.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_RENDERMANAGER_HPP
#define POKEMON_CUSTOM_EVOLUTION_RENDERMANAGER_HPP

#include "TextRenderer.hpp"

class RenderManager
{
    std::vector<Text *> texts;
    glm::mat4 projection;
    TextRenderer *textRenderer;

public:
    RenderManager(TextRenderer *textRenderer);
    void Render();
    void ProcessText(Text *text);
    void ProcessProjection(glm::mat4 projection);
    void Prepare();
    void Clean();
};

#endif //POKEMON_CUSTOM_EVOLUTION_RENDERMANAGER_HPP
