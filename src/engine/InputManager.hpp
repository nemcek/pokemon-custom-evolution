//
// Created by martin on 31.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_INPUTMANAGER_HPP
#define POKEMON_CUSTOM_EVOLUTION_INPUTMANAGER_HPP

#include <GLFW/glfw3.h>

class InputManager
{
private:

    bool *keys;
public:
    InputManager();
    void OnKeyPress(GLFWwindow *, int key, int , int action, int mods);
    bool IsAPressed();
};

#endif //POKEMON_CUSTOM_EVOLUTION_INPUTMANAGER_HPP
