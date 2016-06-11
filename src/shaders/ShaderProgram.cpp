//
// Created by Martin on 14. 5. 2016.
//


#include "src/shaders/ShaderProgram.hpp"

namespace Shaders
{
    ShaderProgram::ShaderProgram(const std::string &vertex_shader_file, const std::string &fragment_shader_file) {
        this->_vertexShaderProgramId = LoadShader(vertex_shader_file, GL_VERTEX_SHADER);
        this->_fragmentShaderProgramId = LoadShader(fragment_shader_file, GL_FRAGMENT_SHADER);
        this->programId = CreateProgram(this->_vertexShaderProgramId, this->_fragmentShaderProgramId);
    }

    ShaderProgram::~ShaderProgram() { }

    GLuint ShaderProgram::LoadShader(const std::string &shader_file, GLuint type) {
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
            std::string vertex_shader_log((unsigned int) info_length, ' ');
            glGetShaderInfoLog(shader_id, info_length, NULL, &vertex_shader_log[0]);
            std::cout << vertex_shader_log << std::endl;
        }

        return shader_id;
    }

    GLuint ShaderProgram::CreateProgram(GLuint vertex_shader_id, GLuint fragment_shader_id) {
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
            std::string program_log((unsigned long) info_length, ' ');
            glGetProgramInfoLog(program_id, info_length, NULL, &program_log[0]);
            std::cout << program_log << std::endl;
        }

        glDeleteShader(vertex_shader_id);
        glDeleteShader(fragment_shader_id);

        return program_id;
    }

    void ShaderProgram::Start() {
        glUseProgram(programId);
    }

    void ShaderProgram::Stop() {
        glUseProgram(0);
    }

    void ShaderProgram::Clean() {
        Stop();
        glDetachShader(programId, this->_vertexShaderProgramId);
        glDetachShader(programId, this->_fragmentShaderProgramId);

        glDeleteShader(this->_vertexShaderProgramId);
        glDeleteShader(this->_fragmentShaderProgramId);

        glDeleteProgram(programId);
    }

    void ShaderProgram::BindAttributes() { }

    void ShaderProgram::BindAttribute(unsigned int attribute, const std::string &varname) {
        glBindAttribLocation(programId, attribute, varname.c_str());
    }

    GLint ShaderProgram::GetUniformLocation(const std::string uniformName) {
        return glGetUniformLocation(programId, uniformName.c_str());
    }

    void ShaderProgram::LoadFloat(GLint location, float value) {
        glUniform1f(location, value);
    }

    void ShaderProgram::LoadInt(GLint location, int value) {
        glUniform1i(location, value);
    }

    void ShaderProgram::LoadVector(GLint location, glm::vec3 vector) {
        glUniform3f(location, vector.x, vector.y, vector.z);
    }

    void ShaderProgram::LoadVector(GLint location, glm::vec2 vector) {
        glUniform2f(location, vector.x, vector.y);
    }

    void ShaderProgram::LoadMatrix(GLint location, glm::mat4 matrix) {
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void ShaderProgram::LoadBoolean(GLint location, bool value) {
        float load;
        if (value)
            load = 1;
        else
            load = 0;

        glUniform1f(location, load);
    }

    void ShaderProgram::LoadTexture(GLint location, GLuint texture_id) {
        // Bind the _texture to "Texture" uniform in program
        glUniform1i(location, 0);
        glActiveTexture(GL_TEXTURE0 + 0);
        glBindTexture(GL_TEXTURE_2D, texture_id);
    }
}