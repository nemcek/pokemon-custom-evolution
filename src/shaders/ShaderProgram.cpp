//
// Created by Martin on 14. 5. 2016.
//


#include "src/shaders/ShaderProgram.hpp"

ShaderProgram::ShaderProgram(const std::string &vertex_shader_file, const std::string &fragment_shader_file) {
    this->vertexShaderProgramId = loadShader(vertex_shader_file, GL_VERTEX_SHADER);
    this->fragmentShaderProgramId = loadShader(fragment_shader_file, GL_FRAGMENT_SHADER);
    this->programId = createProgram(this->vertexShaderProgramId, this->fragmentShaderProgramId);
}

GLuint ShaderProgram::loadShader(const std::string &shader_file, GLuint type) {
    GLint result;
    GLuint shader_id;
    GLint info_length;
    const char *shader_code_ptr;

    info_length = 0;
    result = GL_FALSE;
    shader_id = glCreateShader(type);

    // Load shader code
    std::ifstream shader_stream(shader_file);
    std::string shader_code((std::istreambuf_iterator<char>(shader_stream)),
                            std::istreambuf_iterator<char>());

    // Compile shader
    std::cout << "Compiling Shader ..." << shader_file << std::endl;
    shader_code_ptr = shader_code.c_str();
    glShaderSource(shader_id, 1, &shader_code_ptr, NULL);
    glCompileShader(shader_id);

    // Check vertex shader log
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_length);
        std::string vertex_shader_log((unsigned int)info_length, ' ');
        glGetShaderInfoLog(shader_id, info_length, NULL, &vertex_shader_log[0]);
        std::cout << vertex_shader_log << std::endl;
    }

    return shader_id;
}

GLuint ShaderProgram::createProgram(GLuint vertex_shader_id, GLuint fragment_shader_id) {
    auto result = GL_FALSE;
    auto info_length = 0;

    // Create and link the program
    std::cout << "Linking Shader Program ..." << std::endl;
    auto program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glBindFragDataLocation(program_id, 0, "FragmentColor");
    glLinkProgram(program_id);

    // Check program log
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_length);
        std::string program_log((unsigned long)info_length, ' ');
        glGetProgramInfoLog(program_id, info_length, NULL, &program_log[0]);
        std::cout << program_log << std::endl;
    }

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return program_id;
}

void ShaderProgram::start() {
    glUseProgram(programId);
}

void ShaderProgram::stop() {
    glUseProgram(0);
}

void ShaderProgram::clean() {
    stop();
    glDetachShader(programId, this->vertexShaderProgramId);
    glDetachShader(programId, this->fragmentShaderProgramId);

    glDeleteShader(this->vertexShaderProgramId);
    glDeleteShader(this->fragmentShaderProgramId);

    glDeleteProgram(programId);
}
