//
// Created by martin on 24.05.2016.
//

#include "src/engine/loaders/Loader.hpp"

Loader::Loader(GLuint programId)
{
    this->_programId = programId;
}

Loader::~Loader() { }

RawModelPtr Loader::Load(std::vector<GLfloat> vertex_buffer, std::vector<GLfloat> textcoord_buffer)
{
    RawModelPtr rawModel = std::make_shared<RawModel>();

    glUseProgram(this->_programId);

    // Generate a vertex array object
    glGenVertexArrays(1, &rawModel->vao);
    glBindVertexArray(rawModel->vao);

    // Generate a vertex buffer object
    glGenBuffers(1, &rawModel->vbo);
    LoadVertexBuffer(rawModel->vbo, vertex_buffer);

    // Setup vertex array lookup
    GLuint position_attrib = (GLuint)glGetAttribLocation(this->_programId, "Position");
    glVertexAttribPointer(position_attrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(position_attrib);

    glGenBuffers(1, &rawModel->tbo);
    glBindBuffer(GL_ARRAY_BUFFER, rawModel->tbo);
    glBufferData(GL_ARRAY_BUFFER, textcoord_buffer.size() * sizeof(GLfloat), textcoord_buffer.data(), GL_STATIC_DRAW);

    GLuint texcoord_attrib = (GLuint)glGetAttribLocation(this->_programId, "TexCoord");
    glVertexAttribPointer(texcoord_attrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(texcoord_attrib);

    return rawModel;
}

GLuint Loader::LoadTexture(BitMapPtr bitMap)
{
    GLuint texture_id;
    auto texture_attrib = glGetUniformLocation(this->_programId, "Texture");

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitMap->width, bitMap->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitMap->buffer->data());
    glUniform1i(texture_attrib, 0);
    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    return texture_id;
}

void Loader::LoadVertexBuffer(GLuint location, std::vector<GLfloat> vertex_buffer)
{
    glBindBuffer(GL_ARRAY_BUFFER, location);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer.size() * sizeof(GLfloat), vertex_buffer.data(), GL_STATIC_DRAW);
}
