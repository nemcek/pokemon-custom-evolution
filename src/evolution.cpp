//
// Created by null on 15.5.2016.
//

#include <vector>
#include <iostream>
#include <loaders/ImageLoader.hpp>
#include <images/PngImage.hpp>
#include <loaders/Loader.hpp>
#include <engine/Transformations.hpp>

#include "src/windows/Window.hpp"

int main()
{
    //std::cout << "Running.." << std::endl;

    PngImage *png_image = new PngImage("_data/github.png");

    Window *window = new Window(png_image->bitmap->width, png_image->bitmap->height);
    if (!window->Show())
    {
        std::cerr << "Failed opening window." << std::endl;
        return EXIT_FAILURE;
    }

    window->Load(png_image->bitmap, png_image->color_type);

    // Main execution loop
    while (!glfwWindowShouldClose(window->window))
    {
        if (glfwGetKey(window->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window->window, GL_TRUE);

        if (glfwGetKey(window->window, GLFW_KEY_1) == GLFW_PRESS)
        {
            window->Load(
                    Transformations::Concat(new BitMap(window->width, window->height), Transformations::Scale(png_image->bitmap, png_image->bitmap->width / 2, png_image->bitmap->height / 2), PicturePosition::Center),
                    png_image->color_type);
        }
        else if (glfwGetKey(window->window, GLFW_KEY_W) == GLFW_PRESS)
        {
            window->Load(Transformations::ChangeToWhite(window->bitmap), png_image->color_type);
        }
        else if (glfwGetKey(window->window, GLFW_KEY_B) == GLFW_PRESS)
        {
            window->Load(png_image->bitmap, png_image->color_type);
        }

        // Set gray background
        glClearColor(0,1,0,0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        glfwSwapBuffers(window->window);
        glfwPollEvents();
    }

    // Clean up
    glfwTerminate();

    return EXIT_SUCCESS;
}
