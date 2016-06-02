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
    std::vector<Text *> _texts;
    std::vector<Quad *> _quads;
    TextRenderer *_textRenderer;
    StaticRenderer *_staticRenderer;

public:
    RenderManager(TextRenderer *textRenderer, StaticRenderer *staticRenderer);
    ~RenderManager();
    void Render(glm::mat4 projection);
    void ProcessText(Text *text);
    void ProcessProjection(glm::mat4 projection);
    void ProcessQuad(Quad *quad);
    void Prepare();
    void Clean();
};

typedef std::shared_ptr<RenderManager> RenderManagerPtr;

#endif //POKEMON_CUSTOM_EVOLUTION_RENDERMANAGER_HPP
