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
    void Init();
    void InitializeGeometry();

    std::vector<Pixel> *buffer;
    int width;
    int height;

public:
    Window(int width, int height);
    bool Show();
    void Load(std::vector<Pixel> *buffer, int width, int height, IMAGE_COLOR_TYPE color_type);

    GLFWwindow *window;
    GLuint program_id;
};

typedef std::shared_ptr<Window> WindowPtr;

#endif //POKEMON_CUSTOM_EVOLUTION_WINDOW_HPP
