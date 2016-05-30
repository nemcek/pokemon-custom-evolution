//
// Created by martin on 24.05.2016.
//

#include <vector>
#include <engine/Transformations.hpp>
#include "src/engine/rendering/StaticRenderer.hpp"

StaticRenderer::StaticRenderer(StaticShader *shader)
{
    this->shader = shader;
}

void StaticRenderer::Render(std::vector<Quad *> quads)
{
    for (std::vector<Quad *>::iterator it = quads.begin(); it != quads.end(); it++ ) {
        Render(*it);
    }
}

void StaticRenderer::Render(Quad *quad)
{
    glBindVertexArray(quad->rawModel->vao);
    glBindBuffer(GL_ARRAY_BUFFER, quad->rawModel->vbo);

    glm::vec2 coords = Transformations::ToOpenGLCoords(quad->position, 960, 960);
    this->shader->LoadPosition(coords);

    this->shader->LoadTexture(quad->textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, quad->bitMap->width, quad->bitMap->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, quad->bitMap->buffer->data());

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
