//
// Created by null on 15.5.2016.
//

#include <vector>
#include <iostream>

#include "src/windows/Window.hpp"

int main()
{
    std::cout << "Running.." << std::endl;

    Window *window = new Window();

    if (!window->Show())
    {
        std::cerr << "Failed opening window." << std::endl;
        return EXIT_FAILURE;
    }

    // Main execution loop
    while (!glfwWindowShouldClose(window->window))
    {
        // Set gray background
        glClearColor(.5f,.5f,.5f,0);
        // Clear depth and color buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw triangles using the program
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        // Display result
        glfwSwapBuffers(window->window);
        glfwPollEvents();
    }

    // Clean up
    glfwTerminate();

    return EXIT_SUCCESS;
}
