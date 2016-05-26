//
// Created by martin on 24.05.2016.
//

#include <engine/Transformations.hpp>
#include "src/objects/Quad.hpp"

Quad::Quad(Loader *loader, glm::vec2 position, float scale, BitMap *bitMap)
    : loader(loader),
      position(position),
      scale(scale),
      bitMap(bitMap)
{
    Init();
}

void Quad::Init()
{
    // Setup geometry
    vertex_buffer = {
            // x, y
             1.0f * scale,  1.0f * scale,
            -1.0f * scale,  1.0f * scale,
             1.0f * scale, -1.0f * scale,
            -1.0f * scale, -1.0f * scale
    };

    // Generate another vertex buffer object for texture coordinates
    std::vector<GLfloat> texcoord_buffer {
            // u, v
            1.0f, 0.0f,
            0.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
    };

    this->rawModel = this->loader->Load(vertex_buffer, texcoord_buffer);
    this->textureId = this->loader->LoadTexture(this->bitMap);
}

void Quad::ChangeToWhite()
{
    this->bitMap = Transformations::ChangeToWhite(this->bitMap);
}

void Quad::Animate(float delta) { }

std::vector<GLfloat> Quad::Scale(float scale)
{
    std::vector<GLfloat> scaled(this->vertex_buffer.size());

    for (int i = 0; i < this->vertex_buffer.size(); i++)
        scaled[i] = this->vertex_buffer[i] * scale;

    // apply scaling
    this->loader->LoadVertexBuffer(this->rawModel->vbo, scaled);

    return scaled;
}