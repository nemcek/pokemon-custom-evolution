//
// Created by martin on 24.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_LOADER_HPP
#define POKEMON_CUSTOM_EVOLUTION_LOADER_HPP

#include <GL/glew.h>
#include <objects/RawModel.hpp>
#include <vector>
#include <images/BitMap.hpp>
#include <memory>

using namespace Images;
using namespace Objects;

namespace Engine
{
    namespace Loaders
    {
        class Loader
        {
        public:
            Loader(GLuint programId);
            ~Loader();
            RawModelPtr Load(std::vector<GLfloat> vertex_buffer, std::vector<GLfloat> textcoord_buffer);
            GLuint LoadTexture(BitMapPtr bitMap);
            void LoadVertexBuffer(GLuint location, std::vector<GLfloat> vertex_buffer);

        private:
            GLuint _programId;
        };

        typedef std::shared_ptr<Loader> LoaderPtr;
    }
}
#endif //POKEMON_CUSTOM_EVOLUTION_LOADER_HPP
