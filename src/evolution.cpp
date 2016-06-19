#include <images/PngImage.hpp>
#include <GLFW/glfw3.h>
#include <windows/Window.hpp>
#include <scenes/Scene.hpp>
#include <engine/InputManager.hpp>
#include <constants/Constants.hpp>
#include <pthread.h>
#include <signal.h>

using namespace Windows;
using namespace Scenes;

float currentFrameTime;
float lastFrameTime;
float frameTimeDelta;
InputManagerPtr inputManager;

void OnKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods) {
    inputManager->OnKeyPress(window, key, scancode, action, mods);
}

void OnMouseMove(GLFWwindow* window, double xpos, double ypos) {
    inputManager->OnMouseMove(window, xpos, ypos);
}

void OnMouseButtonClick(GLFWwindow* window, int button, int action, int mods) {
    inputManager->OnMouseButtonClick(window, button, action, mods);
}

float getCurrentTime() {
    return (float) (glfwGetTime() * 1000.0f);
}

void *PlaySound(void *)
{
    system("canberra-gtk-play -f \"/home/martin/Projects/pokemon-custom-evolution/data/evolution_music.wav\"");

    return NULL;
}

int main(int argc, char** argv)
{
//    pthread_t soundThread;
//
//    int rc = pthread_create(&soundThread,
//                            NULL,
//                            PlaySound,
//                            NULL);
//    if (rc){
//        std::cout << "Error:unable to create thread," << rc << std::endl;
//        exit(-1);
//    }

    // quick and dirty way
//    pid_t sid;
//    pid_t pid = fork();
//    if (pid == 0) {
//        sid = system("canberra-gtk-play -f \"/home/martin/Projects/pokemon-custom-evolution/data/evolution_music.wav\"");
//        exit(0);
//    }

    Window *window = new Window(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT);
    window->Show();
    inputManager = std::make_shared<InputManager>();
    ScenePtr scene = std::make_shared<Scene>(inputManager);

    glfwSetKeyCallback(window->window, OnKeyPress);
    glfwSetCursorPosCallback(window->window, OnMouseMove);
    glfwSetMouseButtonCallback(window->window, OnMouseButtonClick);

    while (!glfwWindowShouldClose(window->window))
    {
        // Check and call events
        glfwPollEvents();

        scene->Update(frameTimeDelta);
        scene->Animate(frameTimeDelta);
        scene->Render();

        // Swap the buffers
        glfwSwapBuffers(window->window);

        float currentFrameTime = getCurrentTime();
        frameTimeDelta = (currentFrameTime - lastFrameTime) / 1000.0f;
        lastFrameTime = currentFrameTime;
    }

//    kill(sid, SIGTERM);
    scene->Clean();

    glfwTerminate();

    return EXIT_SUCCESS;
}