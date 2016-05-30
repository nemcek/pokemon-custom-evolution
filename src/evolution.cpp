
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
#include <objects/EvolutionQuad.hpp>
#include <engine/animation/keyframes/TextKeyFrame.hpp>
#include <engine/animation/keyframes/EvolutionKeyFrame.hpp>

const GLuint WIDTH = 960, HEIGHT = 960;
float currentFrameTime;
float lastFrameTime;
float frameTimeDelta;
char title[256];

float getCurrentTime() {
    return (float) (glfwGetTime() * 1000.0f);
}

void WhatTextDrawFinishedTestCallback()
{
    printf("What?! text drawing finished\n");
}

int main()
{
    title[255] = '\0';

    Window *window = new Window(WIDTH, HEIGHT);

    window->Show();

    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(WIDTH), 0.0f, static_cast<GLfloat>(HEIGHT));

    BitMap *bitMap = new BitMap(WIDTH, HEIGHT);
    bitMap->buffer = new std::vector<Pixel> ((unsigned long)(WIDTH * HEIGHT), {36,87,123,255});

    glm::vec2 mainQuadPos(WIDTH / 2, HEIGHT / 2 + HEIGHT / 6);
    PngImage *png_image = new PngImage("_data/github.png");
    PngImage *background = new PngImage("data/evolution_background.png");
    PngImage *arrow = new PngImage("data/evolution_arrow.png");
    PngImage *googleImage = new PngImage("_data/google.png");
//    PngImage *particleCircleImage = new PngImage("data/evolution_particle_circle.png");
//    PngImage *particleQuadImage = new PngImage("data/evolution_particle_quad.png");
//    PngImage *particleCrossImage = new PngImage("data/evolution_particle_cross.png");
//    PngImage *evolCircleImage = new PngImage("data/evolution_circle.png");

    TextShader *textShader = new TextShader();
    TextRenderer *textRenderer = new TextRenderer(textShader);
    StaticRenderer *staticRenderer = new StaticRenderer(new StaticShader());
    RenderManager *renderManager = new RenderManager(textRenderer, staticRenderer);
    Loader *loader = new Loader(staticRenderer->shader->programId);
    EvolutionQuad *quad = new EvolutionQuad(loader, mainQuadPos, 0.5f, png_image->bitmap, googleImage->bitmap);
    Quad *backgroundQuad = new Quad(loader, glm::vec2(WIDTH/2, HEIGHT/2), 1.0f, background->bitmap);
    Quad *arrowQuad = new Quad(loader, glm::vec2(900.0f, 50.0f), 0.04f, arrow->bitmap);

    // testing new textures
//    Quad *particleCircle = new Quad(loader, glm::vec2(300.0, 300.0), 0.1f, particleCircleImage->bitmap);
//    Quad *particleQuad = new Quad(loader, glm::vec2(400.0, 300.0), 0.1f, particleQuadImage->bitmap);
//    Quad *particleCross = new Quad(loader, glm::vec2(500.0, 300.0), 0.1f, particleCrossImage->bitmap);
//    Quad *evolCircle = new Quad(loader, glm::vec2(WIDTH/2, HEIGHT/2), 1.0f, evolCircleImage->bitmap);

    renderManager->ProcessProjection(projection);
    renderManager->ProcessQuad(backgroundQuad);
    renderManager->ProcessQuad(quad);
    renderManager->ProcessQuad(arrowQuad);
//    renderManager->ProcessQuad(particleCircle);
//    renderManager->ProcessQuad(particleQuad);
//    renderManager->ProcessQuad(particleCross);
//    renderManager->ProcessQuad(evolCircle);

    textShader->Start();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    Font *font = new Font("data/Pokemon.ttf", 48);
    std::string str1 ("What?!");
    Text *text1 = new Text(glm::vec2(55.0f, 190.0f), 1.0f, glm::vec3(0, 0, 0), font);
    std::string str2 ("Your Martin Nemcek");
    Text *text2 = new Text(glm::vec2(55.0f, 120.0f), 1.0f, glm::vec3(0, 0, 0), font);
    std::string str3 ("is evolving!");
    Text *text3 = new Text(glm::vec2(55.0f, 50.0f), 1.0f, glm::vec3(0, 0, 0), font);

    renderManager->ProcessText(text1);
    renderManager->ProcessText(text2);
    renderManager->ProcessText(text3);

    quad->animation = new EvolutionAnimation();
    quad->animation->Add(new EvolutionKeyFrame(0.0, mainQuadPos, 1.0f));
    quad->animation->Add(new EvolutionKeyFrame(1.0, mainQuadPos, .0f, true));
    quad->animation->Add(new EvolutionKeyFrame(2.0, mainQuadPos, 1.0f));

    arrowQuad->animation = new Animation();
    arrowQuad->animation->Add(new KeyFrame(0.0, arrowQuad->position, 1.0f));
    arrowQuad->animation->Add(new KeyFrame(0.5, arrowQuad->position, 1.0f));
    arrowQuad->animation->Add(new KeyFrame(0.5, arrowQuad->position, 0.0f));
    arrowQuad->animation->Add(new KeyFrame(1.0, arrowQuad->position, 0.0f));

    std::string empty("");
    text1->animation = new TextAnimation(false);
    text1->animation->Add(new TextKeyFrame(0.0, text1->position, text1->scale, empty));
    text1->animation->Add(new TextKeyFrame(1.0, text1->position, text1->scale, empty));
    text1->animation->Add(new TextKeyFrame(1.65, text1->position, text1->scale, str1, WhatTextDrawFinishedTestCallback));

    text2->animation = new TextAnimation(false);
//    text2->animation->Add(new TextKeyFrame(0.0, text2->position, 1.0f, empty));
    text2->animation->Add(new TextKeyFrame(0.0, text2->position, 1.0f, empty));
    text2->animation->Add(new TextKeyFrame(2.0, text2->position, 1.0f, str2));

    text3->animation = new TextAnimation(false);
    text3->animation->Add(new TextKeyFrame(0.0, text3->position, 1.0f, empty));
    text3->animation->Add(new TextKeyFrame(2.2, text3->position, 1.0f, empty));
    text3->animation->Add(new TextKeyFrame(3.7f, text3->position, 1.0f, str3));

    bool animateNextText = false;
    while (!glfwWindowShouldClose(window->window))
    {
        if (glfwGetKey(window->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window->window, GL_TRUE);
        else if (glfwGetKey(window->window, GLFW_KEY_W) == GLFW_PRESS)
            quad->ChangeToWhite();
        else if (glfwGetKey(window->window, GLFW_KEY_B) == GLFW_PRESS)
            quad->bitMap = png_image->bitmap;
        else if (glfwGetKey(window->window, GLFW_KEY_A) == GLFW_PRESS)
            animateNextText = true;

        // Check and call events
        glfwPollEvents();

        quad->Animate(frameTimeDelta);
        arrowQuad->Animate(frameTimeDelta);
        text1->Animate(frameTimeDelta);

        if (animateNextText)
        {
            text2->Animate(frameTimeDelta);
            text3->Animate(frameTimeDelta);
        }
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