//
// Created by null on 15.5.2016.
//

#include "src/windows/Window.hpp"

Window::Window(int width, int height) : width(width), height(height)
{
}

Window::~Window() { }

bool Window::Show()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return false;
    }

    // Setup OpenGL context
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Try to create a window
    this->window = glfwCreateWindow(this->width, this->height, "Evolution", NULL, NULL);
    if (this->window == NULL)
    {
        std::cerr << "Failed to open GLFW window, your graphics card is probably only capable of OpenGL 2.1" << std::endl;
        glfwTerminate();
        return false;
    }

    // Finalize window setup
    glfwMakeContextCurrent(this->window);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    glewInit();
    if (!glewIsSupported("GL_VERSION_3_3"))
    {
        std::cerr << "Failed to initialize GLEW with OpenGL 3.3!" << std::endl;
        glfwTerminate();
        return false;
    }

    // Define the viewport dimensions
    glViewport(0, 0, width, height);

    return true;


}