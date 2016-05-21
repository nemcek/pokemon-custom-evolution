//
// Created by Martin on 14. 5. 2016.
//

#include "src/loaders/Loader.hpp"

GLuint Loader::LoadTexture(Image *image, GLuint program_id)
{
    GLuint texture_id;
    auto texture_attrib = glGetUniformLocation(program_id, "Texture");

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    // Set mipmaps
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->bitmap->width, image->bitmap->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->bitmap->buffer->data());
    glUniform1i(texture_attrib, 0);
    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    return texture_id;
}
