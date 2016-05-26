//
// Created by martin on 23.05.2016.
//

#include "src/engine/rendering/RenderManager.hpp"

RenderManager::RenderManager(TextRenderer *textRenderer, StaticRenderer *staticRenderer)
        : textRenderer(textRenderer),
          staticRenderer(staticRenderer)
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void RenderManager::ProcessText(Text *text)
{
    this->texts.push_back(text);
}

void RenderManager::ProcessProjection(glm::mat4 projection)
{
    this->projection = projection;
}

void RenderManager::ProcessQuad(Quad *quad)
{
    this->quads.push_back(quad);
}

void RenderManager::Render()
{
    staticRenderer->shader->Start();
    staticRenderer->Render(this->quads);
    staticRenderer->shader->Stop();

    textRenderer->shader->Start();
    textRenderer->Render(this->texts, this->projection);
    textRenderer->shader->Stop();

    //this->texts.clear();
}

void RenderManager::Prepare()
{
    glClearColor(.5f, .5f, .5f, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderManager::Clean()
{
    this->textRenderer->shader->Clean();
    this->staticRenderer->shader->Clean();
}
