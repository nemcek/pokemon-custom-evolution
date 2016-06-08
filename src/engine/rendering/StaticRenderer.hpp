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
    StaticShaderPtr shader;

    StaticRenderer(StaticShaderPtr &shader);
    ~StaticRenderer();
    void Render(std::vector<QuadPtr &> quad) const;
    void Render(QuadPtr &quad) const;
};

typedef std::shared_ptr<StaticRenderer> StaticRendererPtr;

#endif //POKEMON_CUSTOM_EVOLUTION_STATICRENDERER_HPP
