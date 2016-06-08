//
// Created by martin on 31.05.2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_INPUTMANAGER_HPP
#define POKEMON_CUSTOM_EVOLUTION_INPUTMANAGER_HPP

#include <GLFW/glfw3.h>
#include <memory>

class InputManager
{
private:

    bool *_keys;
public:
    InputManager();
    ~InputManager();
    void OnKeyPress(GLFWwindow *, int key, int , int action, int mods);
    bool IsAPressed() const;
};

typedef std::shared_ptr<InputManager> InputManagerPtr;

#endif //POKEMON_CUSTOM_EVOLUTION_INPUTMANAGER_HPP
