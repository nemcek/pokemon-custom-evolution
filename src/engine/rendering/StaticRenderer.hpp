//
// Created by martin on 24.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_STATICRENDERER_HPP
#define POKEMON_CUSTOM_EVOLUTION_STATICRENDERER_HPP

#include <shaders/StaticShader.hpp>
#include <images/BitMap.hpp>
#include <objects/Quad.hpp>

class StaticRenderer
{
private:

public:
    StaticShader *shader;

    StaticRenderer(StaticShader *shader);
    void Render(std::vector<Quad *> quad);
    void Render(Quad *quad);
};

#endif //POKEMON_CUSTOM_EVOLUTION_STATICRENDERER_HPP
