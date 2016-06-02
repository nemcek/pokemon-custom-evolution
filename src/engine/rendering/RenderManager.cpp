//
// Created by martin on 23.05.2016.
//

#include "src/engine/rendering/RenderManager.hpp"

RenderManager::RenderManager(TextRendererPtr textRenderer, StaticRendererPtr staticRenderer)
        : _textRenderer(textRenderer),
          _staticRenderer(staticRenderer)
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

RenderManager::~RenderManager()
{
    this->_quads.clear();
    this->_texts.clear();
}

void RenderManager::ProcessText(TextPtr text)
{
    this->_texts.push_back(text);
}

void RenderManager::ProcessProjection(glm::mat4 projection)
{
//    this->_projection = _projection;
}

void RenderManager::ProcessQuad(QuadPtr quad)
{
    this->_quads.push_back(quad);
}

void RenderManager::Render(glm::mat4 projection)
{
    _staticRenderer->shader->Start();
    _staticRenderer->Render(this->_quads);
    _staticRenderer->shader->Stop();

    _textRenderer->shader->Start();
    _textRenderer->Render(this->_texts, projection);
    _textRenderer->shader->Stop();

//    this->_texts.clear();
//    this->_quads.clear();
}

void RenderManager::Prepare()
{
    glClearColor(.5f, .5f, .5f, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderManager::Clean()
{
    this->_textRenderer->shader->Clean();
    this->_staticRenderer->shader->Clean();
}
