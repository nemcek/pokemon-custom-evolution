//
// Created by martin on 24.05.2016.
//

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
    std::vector<GLfloat> vertex_buffer {
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
