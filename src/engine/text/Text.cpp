//
// Created by martin on 22.05.2016.
//


#include "src/engine/text/Text.hpp"

Text::Text(std::string text, glm::vec2 position, GLfloat scale, glm::vec3 color, Font *font)
        : text(text),
          position(position),
          scale(scale),
          color(color),
          font(font)
{ }