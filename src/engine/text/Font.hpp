//
// Created by martin on 23.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_FONT_HPP
#define POKEMON_CUSTOM_EVOLUTION_FONT_HPP

#include <GL/glew.h>
#include <glm/detail/type_vec.hpp>
#include <glm/vec2.hpp>
#include <map>
#include <ft2build.h>
#include <memory>
#include FT_FREETYPE_H

struct Character {
    GLuint TextureID;   // ID handle of the glyph _texture
    glm::ivec2 Size;    // Size of glyph
    glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
    GLuint Advance;    // Horizontal offset to advance to next glyph
};

class Font
{
private:
    FT_Library _ft;
    FT_Face _face;
public:
    std::map<GLchar, Character> characters;

    Font(std::string ttfFile, unsigned int size);
    ~Font();
    void InitCharacters();
};

typedef std::shared_ptr<Font> FontPtr;

#endif //POKEMON_CUSTOM_EVOLUTION_FONT_HPP
