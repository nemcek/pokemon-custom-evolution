//
// Created by Martin on 14. 5. 2016.
//

#ifndef POKEMON_CUSTOM_EVOLUTION_SHADERPROGRAM_HPP
#define POKEMON_CUSTOM_EVOLUTION_SHADERPROGRAM_HPP

#include <memory>
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/detail/type_mat.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Shaders
{
    class ShaderProgram
    {
    private:
        GLuint _vertexShaderProgramId;
        GLuint _fragmentShaderProgramId;

        GLuint LoadShader(const std::string &shader_file, GLuint type);
        GLuint CreateProgram(GLuint vertex_shader_id, GLuint fragment_shader_id);

    protected:
        virtual void BindAttributes();
        virtual void GetAllUniformLocations() = 0;
        void BindAttribute(unsigned int attribute, const std::string &varname);
        GLint GetUniformLocation(const std::string uniformName);
        void LoadFloat(GLint location, float value);
        void LoadVector(GLint location, glm::vec3 vector);
        void LoadVector(GLint location, glm::vec2 vector);
        void LoadBoolean(GLint location, bool value);
        void LoadMatrix(GLint location, glm::mat4 matrix);
        void LoadTexture(GLint location, GLuint texture_id);
        void LoadInt(GLint location, int value);

    public:
        GLuint programId;

        ShaderProgram(const std::string &vertex_shader_file, const std::string &fragment_shader_file);
        virtual ~ShaderProgram();
        void Start();
        void Stop();
        void Clean();
    };

    typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;
}
#endif //POKEMON_CUSTOM_EVOLUTION_SHADERPROGRAM_HPP
