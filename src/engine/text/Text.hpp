//
// Created by martin on 22.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_TEXT_HPP
#define POKEMON_CUSTOM_EVOLUTION_TEXT_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <glm/vec2.hpp>
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <string>
#include <map>
#include <ft2build.h>
#include <engine/animation/animations/TextAnimation.hpp>
#include "Font.hpp"

using namespace Engine::nsAnimation::Animations;

namespace Engine
{
    namespace Texts
    {
        class Text
        {
        public:
            std::string text;
            glm::vec2 position;
            GLfloat scale;
            glm::vec3 color;
            FontPtr font;
            TextAnimationPtr animation;

            Text(glm::vec2 position, float scale, glm::vec3 color, FontPtr font);
            Text(std::string text, glm::vec2 position, GLfloat scale, glm::vec3 color, FontPtr font);
            ~Text();
            void SetText(std::string text);
            void Animate(float delta);
            void StopRendering();
            void StartRendering();
            bool ShouldRender();
        private:
            bool _allowRender = true;
        };

        typedef std::shared_ptr<Text> TextPtr;
    }
}
#endif //POKEMON_CUSTOM_EVOLUTION_TEXT_HPP
