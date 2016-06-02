#include <images/PngImage.hpp>
#include <GLFW/glfw3.h>
#include <windows/Window.hpp>
#include <scenes/Scene.hpp>
#include <engine/InputManager.hpp>
#include <constants/Constants.hpp>

float currentFrameTime;
float lastFrameTime;
float frameTimeDelta;
InputManagerPtr inputManager;

void OnKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods) {
    inputManager->OnKeyPress(window, key, scancode, action, mods);
}

float getCurrentTime() {
    return (float) (glfwGetTime() * 1000.0f);
}

int main()
{
    Window *window = new Window(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT);
    window->Show();
    inputManager = std::make_shared<InputManager>();
    ScenePtr scene = std::make_shared<Scene>(inputManager);

    glfwSetKeyCallback(window->window, OnKeyPress);

    while (!glfwWindowShouldClose(window->window))
    {
        // Check and call events
        glfwPollEvents();

        scene->Update();
        scene->Animate(frameTimeDelta);
        scene->Render();

        // Swap the buffers
        glfwSwapBuffers(window->window);

        float currentFrameTime = getCurrentTime();
        frameTimeDelta = (currentFrameTime - lastFrameTime) / 1000.0f;
        lastFrameTime = currentFrameTime;
    }

    scene->Clean();

    glfwTerminate();

    return EXIT_SUCCESS;
}