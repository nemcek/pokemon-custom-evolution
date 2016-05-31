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

class Quad
{
private:
    std::vector<GLfloat> vertex_buffer;

    void Init();

public:
    RawModel *rawModel;
    float scale;
    glm::vec2 position;
    Loader *loader;
    BitMap *bitMap;
    GLuint textureId;
    Animation *animation = nullptr;

    Quad(Loader *loader, glm::vec2 position, float scale, BitMap *bitMap);
    void ChangeToWhite();
    virtual void Animate(float delta);
    std::vector<GLfloat> Scale(float scale);
};



#endif //POKEMON_CUSTOM_EVOLUTION_QUAD_HPP
