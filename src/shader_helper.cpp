#include "shader_helper.hpp"
#include <sstream>
#include <fstream>

ShaderHelper::ShaderHelper(const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename) :
    vertexShaderFilename_(vertexShaderFilename), fragmentShaderFilename_(fragmentShaderFilename)
{
    GLuint vertexShaderId = createVertexShader();
    GLuint fragmentShaderId = createFragmentShader();
    shaderProgramId_ = createShaderProgram(vertexShaderId, fragmentShaderId);
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
}

const std::string ShaderHelper::readFileContents(const std::string& filename) {
    std::string line;
    std::stringstream ss("");
    std::ifstream file;

    // ensure ifstream objects can throw exceptions:
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(filename.c_str());
        ss << file.rdbuf();
        file.close();
        return ss.str();
    }
    catch(std::ifstream::failure& e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
}

GLuint ShaderHelper::createVertexShader() {
    std::string vertexShaderSource = readFileContents(vertexShaderFilename_);
    const char* sourcePtr = vertexShaderSource.c_str();

    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &sourcePtr, NULL);
    glCompileShader(vertexShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    } else {
        return vertexShader;
    }
}

GLuint ShaderHelper::createFragmentShader() {
    std::string fragmentShaderSource = readFileContents(fragmentShaderFilename_);
    const char* sourcePtr = fragmentShaderSource.c_str();

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &sourcePtr, NULL);
    glCompileShader(fragmentShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    } else {
        return fragmentShader;
    }
}

GLuint ShaderHelper::createShaderProgram(GLuint vertexShaderId, GLuint fragmentShaderId) {
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderId);
    glAttachShader(shaderProgram, fragmentShaderId);
    glLinkProgram(shaderProgram);

    return shaderProgram;
}

void ShaderHelper::use() {
    glUseProgram(shaderProgramId_);
}

void ShaderHelper::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(shaderProgramId_, name.c_str()), (int)value);
}

void ShaderHelper::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(shaderProgramId_, name.c_str()), value);
}

void ShaderHelper::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(shaderProgramId_, name.c_str()), value);
}

const GLuint ShaderHelper::getUniformLocation(const std::string& uniformName) const {
    return glGetUniformLocation(shaderProgramId_, uniformName.c_str());
}