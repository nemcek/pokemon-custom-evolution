//
// Created by Martin on 14. 5. 2016.
//

#include "src/loaders/Loader.hpp"

GLuint Loader::LoadTexture(const std::string &image)
{
    png_byte *image_data = nullptr;
    int width;
    int height;

    if (!ImageLoader::LoadPNGImage(image.c_str(), image_data, &width, &height))
    {
        fprintf(stderr, "Unable to open file: %s", image.c_str());
        return 0;
    }

    // Generate the OpenGL texture object
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

    free(image_data);
}
