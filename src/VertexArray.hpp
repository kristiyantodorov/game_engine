#pragma once

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexArray {
public:
    VertexArray();
    ~VertexArray();
    void addBuffer(const VertexBufferLayout& layout, const VertexBuffer& vb);
    void bind() const;
    void unbind() const;
private:
    unsigned int m_Id;
    unsigned int m_Offset;
};