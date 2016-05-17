//
// Created by null on 15.5.2016.
//

#include <vector>
#include <iostream>
#include <loaders/ImageLoader.hpp>
#include <images/PngImage.hpp>

#include "src/windows/Window.hpp"

int main()
{
    std::cout << "Running.." << std::endl;

    Window *window = new Window(512, 512);

    if (!window->Show())
    {
        std::cerr << "Failed opening window." << std::endl;
        return EXIT_FAILURE;
    }

    png_byte *bytes;
    int width, height;
    ImageLoader::LoadPNGImage("_data/opengl.png", bytes, &width, &height);

//    PngImagePtr png_image = new PngImage(bytes, width, height);

    // Main execution loop
    while (!glfwWindowShouldClose(window->window))
    {
        // Set gray background
        glClearColor(0, 0, 0,0);
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
