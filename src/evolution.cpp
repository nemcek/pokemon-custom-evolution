
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

const GLuint WIDTH = 512, HEIGHT = 512;

int main()
{
    // Init GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr); // Windowed
    glfwMakeContextCurrent(window);

    // Initialize GLEW to setup the OpenGL Function pointers
    glewExperimental = GL_TRUE;
    glewInit();
    if (!glewIsSupported("GL_VERSION_3_3"))
    {
        std::cerr << "Failed to initialize GLEW with OpenGL 3.3!" << std::endl;
        glfwTerminate();
        return false;
    }

    // Define the viewport dimensions
    glViewport(0, 0, WIDTH, HEIGHT);

    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(WIDTH), 0.0f, static_cast<GLfloat>(HEIGHT));

    BitMap *bitMap = new BitMap(WIDTH, HEIGHT);
    bitMap->buffer = new std::vector<Pixel> ((unsigned long)(WIDTH * HEIGHT), {36,87,123,255});

    PngImage *png_image = new PngImage("_data/github.png");
    TextShader *textShader = new TextShader();
    TextRenderer *textRenderer = new TextRenderer(textShader);
    StaticRenderer *staticRenderer = new StaticRenderer(new StaticShader());
    RenderManager *renderManager = new RenderManager(textRenderer, staticRenderer);
    Quad *quad = new Quad(new Loader(staticRenderer->shader->programId), glm::vec2(256.0, 256.0), 0.5f, bitMap);
    Quad *quad2 = new Quad(new Loader(staticRenderer->shader->programId), glm::vec2(384.0, 384.0), 0.3f, png_image->bitmap);

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

    glBindTexture(GL_TEXTURE_2D, 0);

    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);

        // Check and call events
        glfwPollEvents();

        renderManager->Prepare();
        renderManager->Render();

        // Swap the buffers
        glfwSwapBuffers(window);
    }

    renderManager->Clean();

    glfwTerminate();

    return EXIT_SUCCESS;
}