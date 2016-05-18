//
// Created by martin on 18.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_MANIPULATIONS_HPP
#define POKEMON_CUSTOM_EVOLUTION_MANIPULATIONS_HPP

#include <images/Image.hpp>

class Manipulations
{
public:
    static std::vector<Pixel> *Scale(std::vector <Pixel> *buffer, int width, int height, int new_width, int new_height);
};

#endif //POKEMON_CUSTOM_EVOLUTION_MANIPULATIONS_HPP
