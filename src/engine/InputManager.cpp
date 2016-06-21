//
// Created by martin on 31.05.2016.
//

#include <glm/glm.hpp>
#include <constants/Constants.hpp>
#include "InputManager.hpp"

namespace Engine
{
    InputManager::InputManager() {
        this->_keys = new bool[1024]{false};
    }

    InputManager::~InputManager() {
        delete[] _keys;
    }

    void InputManager::OnKeyPress(GLFWwindow *window, int key, int, int action, int) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);

        if (key >= 0 && key < 1024) {
            if (action == GLFW_PRESS)
                _keys[key] = true;
            else if (action == GLFW_RELEASE)
                _keys[key] = false;
        }
    }

    void InputManager::OnMouseButtonClick(GLFWwindow *window, int button, int action, int mods) {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        y = glm::abs(Constants::WINDOW_HEIGHT - y);
    }

    void InputManager::OnMouseMove(GLFWwindow *window, double xpos, double ypos) {
//        double x, y;
//        glfwGetCursorPos(window, &x, &y);

//        y = glm::abs(Constants::WINDOW_HEIGHT - y);
//
//        snprintf(_titleBuffer, 255, "[%i, %i]", static_cast<int>(x), static_cast<int>(y));
//
//        // Sets coordinates into title
//        glfwSetWindowTitle(window, _titleBuffer);
    }

    bool InputManager::IsAPressed() {
        return this->_keys[GLFW_KEY_A];
    }

    bool InputManager::IsEnterPressed() {
        return this->_keys[GLFW_KEY_ENTER];
    }
}