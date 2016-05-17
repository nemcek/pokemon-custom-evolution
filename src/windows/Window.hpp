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

    GLuint program_id;
    ImagePtr image;
    int width;
    int height;

public:
    Window(int width, int height);
    bool Show();
    void Update();
    void LoadImage(ImagePtr image);

    GLFWwindow *window;
};

typedef std::shared_ptr<Window> WindowPtr;

#endif //POKEMON_CUSTOM_EVOLUTION_WINDOW_HPP
