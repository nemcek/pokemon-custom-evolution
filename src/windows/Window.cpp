//
// Created by null on 15.5.2016.
//

#include "src/windows/Window.hpp"

Window::Window(int width, int height) : width(width), height(height)
{
    Init();
}

bool Window::Show()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return false;
    }

    // Setup OpenGL context
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Try to create a window
    this->window = glfwCreateWindow(this->width, this->height, "Evolution", NULL, NULL);
    if (this->window == NULL)
    {
        std::cerr << "Failed to open GLFW window, your graphics card is probably only capable of OpenGL 2.1" << std::endl;
        glfwTerminate();
        return false;
    }

    // Finalize window setup
    glfwMakeContextCurrent(this->window);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    glewInit();
    if (!glewIsSupported("GL_VERSION_3_3"))
    {
        std::cerr << "Failed to initialize GLEW with OpenGL 3.3!" << std::endl;
        glfwTerminate();
        return false;
    }

    // Load shaders
    this->program_id = ShaderProgram("src/shaders/vert_texture.glsl", "src/shaders/frag_texture.glsl").programId;
    glUseProgram(this->program_id);

    InitializeGeometry();

    return true;

}

void Window::Init()
{
}

void Window::InitializeGeometry()
{
    // Generate a vertex array object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Setup geometry
    std::vector<GLfloat> vertex_buffer {
            // x, y
            1.0f, 1.0f,
            -1.0f, 1.0f,
            1.0f, -1.0f,
            -1.0f, -1.0f
    };

    // Generate a vertex buffer object
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer.size() * sizeof(GLfloat), vertex_buffer.data(), GL_STATIC_DRAW);

    // Setup vertex array lookup
    GLuint position_attrib = (GLuint)glGetAttribLocation(this->program_id, "Position");
    glVertexAttribPointer(position_attrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(position_attrib);

    // Generate another vertex buffer object for texture coordinates
    std::vector<GLfloat> texcoord_buffer {
            // u, v
            1.0f, 0.0f,
            0.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
    };

    GLuint tbo;
    glGenBuffers(1, &tbo);
    glBindBuffer(GL_ARRAY_BUFFER, tbo);
    glBufferData(GL_ARRAY_BUFFER, texcoord_buffer.size() * sizeof(GLfloat), texcoord_buffer.data(), GL_STATIC_DRAW);

    GLuint texcoord_attrib = (GLuint)glGetAttribLocation(this->program_id, "TexCoord");
    glVertexAttribPointer(texcoord_attrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(texcoord_attrib);
}

void Window::LoadImage(ImagePtr image)
{
    this->image = image;
}

void Window::Update()
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->image->width, this->image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->image->buffer->data());
}

