#include "ShaderHelper.hpp"
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

const std::string ShaderHelper::readFileContents(const std::string& fileuniformName) {
    std::string line;
    std::stringstream ss("");
    std::ifstream file;

    // ensure ifstream objects can throw exceptions:
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(fileuniformName.c_str());
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

void ShaderHelper::setBool(const std::string &uniformName, bool value) const {
    glUniform1i(glGetUniformLocation(shaderProgramId_, uniformName.c_str()), (int)value);
}

void ShaderHelper::setInt(const std::string &uniformName, int value) const {
    glUniform1i(glGetUniformLocation(shaderProgramId_, uniformName.c_str()), value);
}

void ShaderHelper::setFloat(const std::string &uniformName, float value) const {
    glUniform1f(glGetUniformLocation(shaderProgramId_, uniformName.c_str()), value);
}

const GLuint ShaderHelper::getUniformLocation(const std::string& uniformName) const {
    return glGetUniformLocation(shaderProgramId_, uniformName.c_str());
}

void ShaderHelper::setVec2(const std::string &uniformName, const glm::vec2 &value) const { 
    glUniform2fv(glGetUniformLocation(shaderProgramId_, uniformName.c_str()), 1, &value[0]); 
}

void ShaderHelper::setVec2(const std::string &uniformName, float x, float y) const { 
    glUniform2f(glGetUniformLocation(shaderProgramId_, uniformName.c_str()), x, y); 
}

// ------------------------------------------------------------------------
void ShaderHelper::setVec3(const std::string &uniformName, const glm::vec3 &value) const { 
    glUniform3fv(glGetUniformLocation(shaderProgramId_, uniformName.c_str()), 1, &value[0]); 
}

void ShaderHelper::setVec3(const std::string &uniformName, float x, float y, float z) const { 
    glUniform3f(glGetUniformLocation(shaderProgramId_, uniformName.c_str()), x, y, z); 
}

// ------------------------------------------------------------------------
void ShaderHelper::setVec4(const std::string &uniformName, const glm::vec4 &value) const { 
    glUniform4fv(glGetUniformLocation(shaderProgramId_, uniformName.c_str()), 1, &value[0]); 
}

void ShaderHelper::setVec4(const std::string &uniformName, float x, float y, float z, float w) { 
    glUniform4f(glGetUniformLocation(shaderProgramId_, uniformName.c_str()), x, y, z, w); 
}

// ------------------------------------------------------------------------
void ShaderHelper::setMat2(const std::string &uniformName, const glm::mat2 &mat) const {
    glUniformMatrix2fv(glGetUniformLocation(shaderProgramId_, uniformName.c_str()), 1, GL_FALSE, &mat[0][0]);
}

// ------------------------------------------------------------------------
void ShaderHelper::setMat3(const std::string &uniformName, const glm::mat3 &mat) const {
    glUniformMatrix3fv(glGetUniformLocation(shaderProgramId_, uniformName.c_str()), 1, GL_FALSE, &mat[0][0]);
}

// ------------------------------------------------------------------------
void ShaderHelper::setMat4(const std::string &uniformName, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramId_, uniformName.c_str()), 1, GL_FALSE, &mat[0][0]);
}
