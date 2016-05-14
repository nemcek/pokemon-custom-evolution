//
// Created by Martin on 14. 5. 2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_SHADERPROGRAM_HPP
#define POKEMON_CUSTOM_EVOLUTION_SHADERPROGRAM_HPP

#include <memory>
#include <iostream>
#include <fstream>
#include <GL/glew.h>

class ShaderProgram {
private:
    GLuint vertexShaderProgramId;
    GLuint fragmentShaderProgramId;

    GLuint loadShader(const std::string &shader_file, GLuint type);
    GLuint createProgram(GLuint vertex_shader_id, GLuint fragment_shader_id);

public:
    GLuint programId;

    ShaderProgram(const std::string &vertex_shader_file, const std::string &fragment_shader_file);
    void start();
    void stop();
    void clean();

};

typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;

#endif //POKEMON_CUSTOM_EVOLUTION_SHADERPROGRAM_HPP
