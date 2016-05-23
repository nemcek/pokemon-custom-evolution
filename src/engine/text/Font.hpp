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
#include FT_FREETYPE_H

struct Character {
    GLuint TextureID;   // ID handle of the glyph texture
    glm::ivec2 Size;    // Size of glyph
    glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
    GLuint Advance;    // Horizontal offset to advance to next glyph
};

class Font
{
private:
    FT_Library ft;
    FT_Face face;
public:
    std::map<GLchar, Character> characters;
    Font(std::string ttfFile, unsigned int size);
    void InitCharacters();
};

#endif //POKEMON_CUSTOM_EVOLUTION_FONT_HPP
