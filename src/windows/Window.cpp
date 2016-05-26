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
//    ShaderProgram *program = new ShaderProgram("src/shaders/vert_texture.glsl", "src/shaders/frag_texture.glsl");
//    this->program_id = program->programId;
//    program->start();
//
//    InitializeGeometry();
//    InitializeTexture();
//
//    program->stop();

    return true;

}

void Window::Init()
{
    this->bitmap = new BitMap(this->width, this->height);
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
//            1.0f, 1.0f,
//            -1.0f, 1.0f,
//            1.0f, -1.0f,
//            -1.0f, -1.0f
             .5f, .5f,
            -.5f, .5f,
            .5f, -.5f,
            -.5f, -.5f

    };

    // Generate a vertex buffer object
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer.size() * sizeof(GLfloat), vertex_buffer.data(), GL_STATIC_DRAW);

    // Setup vertex array lookup
//    GLuint position_attrib = (GLuint)glGetAttribLocation(this->program_id, "Position");
//    glVertexAttribPointer(position_attrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
//    glEnableVertexAttribArray(position_attrib);

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

//    GLuint texcoord_attrib = (GLuint)glGetAttribLocation(this->program_id, "TexCoord");
//    glVertexAttribPointer(texcoord_attrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
//    glEnableVertexAttribArray(texcoord_attrib);
}

GLuint Window::InitializeTexture()
{
    GLuint texture_id;
//    auto texture_attrib = glGetUniformLocation(program_id, "Texture");

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    // Set mipmaps
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->bitmap->width, this->bitmap->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->bitmap->buffer->data());
//    glUniform1i(texture_attrib, 0);
    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    return texture_id;
}

void Window::Load(BitMap *bitmap, IMAGE_COLOR_TYPE color_type)
{
    this->bitmap = bitmap;
    GLuint gl_color_type = color_type == IMAGE_COLOR_TYPE::RGB ? GL_RGB : GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, gl_color_type, bitmap->width, bitmap->height, 0, gl_color_type, GL_UNSIGNED_BYTE, bitmap->buffer->data());
}

