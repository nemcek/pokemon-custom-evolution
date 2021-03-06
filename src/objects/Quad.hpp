//
// Created by martin on 24.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_QUAD_HPP
#define POKEMON_CUSTOM_EVOLUTION_QUAD_HPP

#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <engine/loaders/Loader.hpp>
#include <images/BitMap.hpp>
#include <engine/animation/animations/Animation.hpp>

using namespace Engine;
using namespace Engine::Loaders;
using namespace Images;
using namespace Engine::nsAnimation::Animations;

namespace Objects
{
    class Quad
    {
    private:
        std::vector<GLfloat> _vertexBuffer;

        void Init();
    public:
        RawModelPtr rawModel;
        float scaleX;
        float scaleY;
        glm::vec2 position;
        LoaderPtr loader;
        BitMapPtr bitMap;
        GLuint textureId;
        AnimationPtr animation = nullptr;
        bool renderAllowed = true;
        bool renderStoped = false;
        float renderDelay = 0.0f;

        Quad(LoaderPtr loader, glm::vec2 position, float scale, BitMapPtr bitMap);
        Quad(LoaderPtr loader, glm::vec2 position, float scaleX, float scaleY, BitMapPtr bitMap);
        virtual ~Quad();
        void ChangeToWhite();
        virtual void Animate(float delta);
        virtual void Update(float delta);
        std::vector<GLfloat> Scale(glm::vec2 scale);

    protected:
        float _timeDelayed = 0.0f;

    };

    typedef std::shared_ptr<Quad> QuadPtr;
}
#endif //POKEMON_CUSTOM_EVOLUTION_QUAD_HPP
