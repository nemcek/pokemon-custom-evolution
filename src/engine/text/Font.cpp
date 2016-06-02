//
// Created by martin on 23.05.2016.
//

#include <iostream>
#include "src/engine/text/Font.hpp"

Font::Font(std::string ttfFile, unsigned int size)
{
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&_ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

    if (FT_New_Face(_ft, ttfFile.c_str(), 0, &_face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

    // Set size to load glyphs as
    FT_Set_Pixel_Sizes(_face, 0, size);

    InitCharacters();
}

Font::~Font() { }

void Font::InitCharacters()
{
    for (GLubyte c = 0; c < 128; c++)
    {
        // Load character glyph
        if (FT_Load_Char(_face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // Generate _texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                _face->glyph->bitmap.width,
                _face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                _face->glyph->bitmap.buffer
        );
        // Set _texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use
        Character character = {
                texture,
                glm::ivec2(_face->glyph->bitmap.width, _face->glyph->bitmap.rows),
                glm::ivec2(_face->glyph->bitmap_left, _face->glyph->bitmap_top),
                _face->glyph->advance.x
        };
        characters.insert(std::pair<GLchar, Character>(c, character));
    }
}
