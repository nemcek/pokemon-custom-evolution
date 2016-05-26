//
// Created by null on 15.5.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_WINDOW_HPP
#define POKEMON_CUSTOM_EVOLUTION_WINDOW_HPP

#include <GL/glew.h>
#include <vector>
#include <GLFW/glfw3.h>
#include <iostream>
#include <shaders/ShaderProgram.hpp>
#include "src/images/Image.hpp"

class Window
{
private:

public:
    Window(int width, int height);
    bool Show();

    GLFWwindow *window;
    int width;
    int height;
};

#endif //POKEMON_CUSTOM_EVOLUTION_WINDOW_HPP
