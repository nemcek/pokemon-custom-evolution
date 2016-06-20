//
// Created by martin on 22.05.2016.
//


#include "src/engine/text/Text.hpp"

namespace Engine
{
    namespace Texts
    {
        Text::Text(glm::vec2 position, float scale, glm::vec3 color, FontPtr font)
                : position(position),
                  scale(scale),
                  color(color),
                  font(font) {
            text = std::string("");
        }

        Text::Text(std::string text, glm::vec2 position, GLfloat scale, glm::vec3 color, FontPtr font)
                : text(text),
                  position(position),
                  scale(scale),
                  color(color),
                  font(font) {
        }

        Text::~Text() {
        }

        void Text::SetText(std::string text) {
            this->text = text;
        }

        void Text::Animate(float delta) {
            if (this->animation != nullptr) {
                this->animation->Animate(delta);
                this->position = this->animation->position;
                this->scale = this->animation->scale;
                this->SetText(this->animation->text);
            }
        }

        bool Text::ShouldRender() {
            return _allowRender;
        }

        void Text::StopRendering() {
            this->_allowRender = false;
        }
    }
}