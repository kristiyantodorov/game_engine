#ifndef SHADER_HELPERS_HPP
#define SHADER_HELPERS_HPP

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <iostream>
#include "vendor/glm/glm.hpp"

class ShaderHelper {
public:
    ShaderHelper(const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename);

    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string &name, const glm::vec2 &value) const;
    void setVec2(const std::string &name, float x, float y) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w);
    void setMat2(const std::string &name, const glm::mat2 &mat) const;
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
    const GLuint getUniformLocation(const std::string& uniformName) const;

private:
    const std::string readFileContents(const std::string& filename);
    GLuint createVertexShader();
    GLuint createFragmentShader();
    GLuint createShaderProgram(GLuint vertexShaderId, GLuint fragmentShaderId);

    std::string vertexShaderFilename_, fragmentShaderFilename_;
    GLuint shaderProgramId_;
};

#endif