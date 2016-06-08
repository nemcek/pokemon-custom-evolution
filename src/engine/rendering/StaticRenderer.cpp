//
// Created by martin on 24.05.2016.
//

#include <vector>
#include <engine/Transformations.hpp>
#include <constants/Constants.hpp>
#include "src/engine/rendering/StaticRenderer.hpp"

StaticRenderer::StaticRenderer(StaticShaderPtr &shader)
{
    this->shader = shader;
}

StaticRenderer::~StaticRenderer() { }

void StaticRenderer::Render(std::vector<QuadPtr> quads) const
{
    for (QuadPtr quad : quads ) {
        Render(quad);
    }
}

void StaticRenderer::Render(QuadPtr &quad) const
{
    glBindVertexArray(quad->rawModel->vao);
    glBindBuffer(GL_ARRAY_BUFFER, quad->rawModel->vbo);

    glm::vec2 coords = Transformations::ToOpenGLCoords(quad->position, Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT);
    this->shader->LoadPosition(coords);

    this->shader->LoadTexture(quad->textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (*quad->bitMap)->width, (*quad->bitMap)->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (*quad->bitMap->buffer)->data());

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
