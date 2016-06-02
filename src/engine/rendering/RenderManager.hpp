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
    std::vector<TextPtr> _texts;
    std::vector<QuadPtr> _quads;
    TextRendererPtr _textRenderer;
    StaticRendererPtr _staticRenderer;

public:
    RenderManager(TextRendererPtr textRenderer, StaticRendererPtr staticRenderer);
    ~RenderManager();
    void Render(glm::mat4 projection);
    void ProcessText(TextPtr text);
    void ProcessProjection(glm::mat4 projection);
    void ProcessQuad(QuadPtr quad);
    void Prepare();
    void Clean();
};

typedef std::shared_ptr<RenderManager> RenderManagerPtr;

#endif //POKEMON_CUSTOM_EVOLUTION_RENDERMANAGER_HPP
