//
// Created by martin on 24.05.2016.
//

#include <engine/Transformations.hpp>
#include "src/objects/Quad.hpp"

Quad::Quad(LoaderPtr loader, glm::vec2 position, float scale, BitMapPtr bitMap)
    : loader(loader),
      position(position),
      scale(scale),
      bitMap(bitMap)
{
    Init();
}

Quad::~Quad() { }

void Quad::Init()
{
    // Setup geometry
    _vertexBuffer = {
            // x, y
             1.0f * scale,  1.0f * scale,
            -1.0f * scale,  1.0f * scale,
             1.0f * scale, -1.0f * scale,
            -1.0f * scale, -1.0f * scale
    };

    // Generate another vertex buffer object for _texture coordinates
    std::vector<GLfloat> texcoord_buffer {
            // u, v
            1.0f, 0.0f,
            0.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
    };

    this->rawModel = this->loader->Load(_vertexBuffer, texcoord_buffer);
    this->textureId = this->loader->LoadTexture(this->bitMap);
}

void Quad::ChangeToWhite()
{
    this->bitMap = Transformations::ChangeToWhite(this->bitMap);
}

void Quad::Animate(float delta)
{
    if (this->animation != nullptr)
    {
        this->animation->Animate(delta);
        this->position = this->animation->position;
        this->Scale(this->animation->scale);
    }
}

std::vector<GLfloat> Quad::Scale(float scale)
{
    std::vector<GLfloat> scaled(this->_vertexBuffer.size());

    for (int i = 0; i < this->_vertexBuffer.size(); i++)
        scaled[i] = this->_vertexBuffer[i] * scale;

    // apply scaling
    this->loader->LoadVertexBuffer(this->rawModel->vbo, scaled);

    return scaled;
}