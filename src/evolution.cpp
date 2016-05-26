
#include <images/PngImage.hpp>
#include <iostream>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <shaders/ShaderProgram.hpp>
#include <shaders/TextShader.hpp>
#include <engine/rendering/TextRenderer.hpp>
#include <engine/rendering/RenderManager.hpp>
#include <windows/Window.hpp>
#include <objects/AnimatedQuad.hpp>

const GLuint WIDTH = 512, HEIGHT = 512;
float currentFrameTime;
float lastFrameTime;
float frameTimeDelta;
char title[256];

float getCurrentTime() {
    return (float) (glfwGetTime() * 1000.0f);
}

int main()
{
    title[255] = '\0';

    Window *window = new Window(WIDTH, HEIGHT);

    window->Show();

    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(WIDTH), 0.0f, static_cast<GLfloat>(HEIGHT));

    BitMap *bitMap = new BitMap(WIDTH, HEIGHT);
    bitMap->buffer = new std::vector<Pixel> ((unsigned long)(WIDTH * HEIGHT), {36,87,123,255});

    PngImage *png_image = new PngImage("_data/github.png");
    TextShader *textShader = new TextShader();
    TextRenderer *textRenderer = new TextRenderer(textShader);
    StaticRenderer *staticRenderer = new StaticRenderer(new StaticShader());
    RenderManager *renderManager = new RenderManager(textRenderer, staticRenderer);
    AnimatedQuad *quad = new AnimatedQuad(new Loader(staticRenderer->shader->programId), glm::vec2(256.0, 256.0), 0.5f, png_image->bitmap);
    Quad *quad2 = new Quad(new Loader(staticRenderer->shader->programId), glm::vec2(128.0, 384.0), 0.3f, bitMap);

    renderManager->ProcessProjection(projection);
    renderManager->ProcessQuad(quad);
    renderManager->ProcessQuad(quad2);
    textShader->Start();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    Font *font = new Font("_data/Ubuntu-MI.ttf", 48);
    std::string str1 ("What?");
    Text *text1 = new Text(str1, glm::vec2(20.0f, 80.0f), .3f, glm::vec3(0, 0, 0), font);
    std::string str2 ("Your Martin Nemcek is evolving!");
    Text *text2 = new Text(str2, glm::vec2(20.0f, 60.0f), 0.35f, glm::vec3(0, 0, 0), font);

    renderManager->ProcessText(text1);
    renderManager->ProcessText(text2);

//    glBindTexture(GL_TEXTURE_2D, 0);

    quad->animation = new Animation();
//    quad->animation->Add(new KeyFrame(0.0, glm::vec2(256, 256), 1.0f));
//    quad->animation->Add(new KeyFrame(1.0, glm::vec2(384, 384), 0.3f));
//    quad->animation->Add(new KeyFrame(2.0, glm::vec2(512, 512), 1.0f));
//    quad->animation->Add(new KeyFrame(3.0, glm::vec2(384, 384), 0.3f));
//    quad->animation->Add(new KeyFrame(4.0, glm::vec2(256, 256), 1.0f));
    quad->animation->Add(new KeyFrame(0.0, glm::vec2(256, 256), 1.0f));
    quad->animation->Add(new KeyFrame(1.0, glm::vec2(256, 256), 0.66f));
    quad->animation->Add(new KeyFrame(2.0, glm::vec2(256, 256), 0.33f));
    quad->animation->Add(new KeyFrame(3.0, glm::vec2(256, 256), .0f));
    quad->animation->Add(new KeyFrame(4.0, glm::vec2(256, 256), .33f));
    quad->animation->Add(new KeyFrame(5.0, glm::vec2(256, 256), .66f));
    quad->animation->Add(new KeyFrame(6.0, glm::vec2(256, 256), 1.0f));


    while (!glfwWindowShouldClose(window->window))
    {
        if (glfwGetKey(window->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window->window, GL_TRUE);
        else if (glfwGetKey(window->window, GLFW_KEY_W) == GLFW_PRESS)
            quad->ChangeToWhite();
        else if (glfwGetKey(window->window, GLFW_KEY_B) == GLFW_PRESS)
            quad->bitMap = png_image->bitmap;

        // Check and call events
        glfwPollEvents();

        quad->Animate(frameTimeDelta);
        renderManager->Prepare();
        renderManager->Render();

        // Swap the buffers
        glfwSwapBuffers(window->window);

        float currentFrameTime = getCurrentTime();
        frameTimeDelta = (currentFrameTime - lastFrameTime) / 1000.0f;
        lastFrameTime = currentFrameTime;
    }

    renderManager->Clean();

    glfwTerminate();

    return EXIT_SUCCESS;
}