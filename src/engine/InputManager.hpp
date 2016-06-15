//
// Created by martin on 31.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_INPUTMANAGER_HPP
#define POKEMON_CUSTOM_EVOLUTION_INPUTMANAGER_HPP

#include <GLFW/glfw3.h>
#include <memory>

namespace Engine
{
    class InputManager
    {
    public:
        InputManager();
        ~InputManager();
        void OnKeyPress(GLFWwindow *, int key, int, int action, int mods);
        void OnMouseMove(GLFWwindow* window, double xpos, double ypos);
        void OnMouseButtonClick(GLFWwindow* window, int button, int action, int mods);
        bool IsAPressed();
    private:
        bool *_keys;
        char _titleBuffer[256] = {'\0'};
    };

    typedef std::shared_ptr<InputManager> InputManagerPtr;
}
#endif //POKEMON_CUSTOM_EVOLUTION_INPUTMANAGER_HPP
