//
// Created by null on 15.5.2016.
//

#include <vector>
#include <iostream>
#include <loaders/ImageLoader.hpp>
#include <images/PngImage.hpp>
#include <loaders/Loader.hpp>

#include "src/windows/Window.hpp"

int main()
{
    std::cout << "Running.." << std::endl;

    Window *window = new Window(1024, 512);

    if (!window->Show())
    {
        std::cerr << "Failed opening window." << std::endl;
        return EXIT_FAILURE;
    }

    PngImage *png_image = new PngImage("_data/opengl.png");

    Loader::LoadTexture(png_image, window->program_id);

    // Main execution loop
    while (!glfwWindowShouldClose(window->window))
    {
        if (glfwGetKey(window->window, GLFW_KEY_W) == GLFW_PRESS)
            window->Load(png_image->ChangeToWhite(), png_image->width, png_image->height, png_image->color_type);
        else if (glfwGetKey(window->window, GLFW_KEY_B) == GLFW_PRESS)
            window->Load(png_image->buffer, png_image->width, png_image->height, png_image->color_type);


        glClearColor(0, 0, 0,0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        glfwSwapBuffers(window->window);
        glfwPollEvents();
    }

    // Clean up
    glfwTerminate();

    return EXIT_SUCCESS;
}
