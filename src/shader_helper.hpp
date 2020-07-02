#ifndef SHADER_HELPERS_HPP
#define SHADER_HELPERS_HPP

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <iostream>

class ShaderHelper {
public:
    ShaderHelper(const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename);

    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
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