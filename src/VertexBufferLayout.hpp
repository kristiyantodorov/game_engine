#pragma once

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

#include <vector>

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int getSizeOfType(unsigned int type) {
        switch(type) {
            case GL_FLOAT:          return 4;
            case GL_UNSIGNED_INT:   return 4;
            case GL_UNSIGNED_BYTE:  return 1;
        }
    }
};

class VertexBufferLayout {
public:
    VertexBufferLayout();

    template <typename T>
    void push(unsigned int count);

    inline unsigned int getStride() const { return m_Stride; }
    inline const std::vector<VertexBufferElement>& getElements() const { return m_Elements; }

private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;
};