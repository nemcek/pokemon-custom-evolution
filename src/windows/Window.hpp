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

class Window
{
private:
    void Init();
    void InitializeGeometry();

    GLuint program_id;
public:
    Window();
    bool Show();

    GLFWwindow *window;
};

#endif //POKEMON_CUSTOM_EVOLUTION_WINDOW_HPP
