//
// Created by martin on 23.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_RENDERMANAGER_HPP
#define POKEMON_CUSTOM_EVOLUTION_RENDERMANAGER_HPP

#include "TextRenderer.hpp"
#include "StaticRenderer.hpp"

class RenderManager
{
private:
    std::vector<Text *> texts;
    std::vector<Quad *> quads;
    TextRenderer *textRenderer;
    StaticRenderer *staticRenderer;

public:
    RenderManager(TextRenderer *textRenderer, StaticRenderer *staticRenderer);
    void Render(glm::mat4 projection);
    void ProcessText(Text *text);
    void ProcessProjection(glm::mat4 projection);
    void ProcessQuad(Quad *quad);
    void Prepare();
    void Clean();
};

#endif //POKEMON_CUSTOM_EVOLUTION_RENDERMANAGER_HPP
