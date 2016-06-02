//
// Created by martin on 31.05.2016.
//

#include "InputManager.hpp"

InputManager::InputManager()
{
    this->_keys = new bool[1024]{false};
}

InputManager::~InputManager()
{
    delete[] _keys;
}

void InputManager::OnKeyPress(GLFWwindow *window, int key, int , int action, int ) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS)
            _keys[key] = true;
        else if (action == GLFW_RELEASE)
            _keys[key] = false;
    }
}

bool InputManager::IsAPressed()
{
    return this->_keys[GLFW_KEY_A];
}