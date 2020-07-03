#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

VertexArray::VertexArray() : m_Offset(0) {
    glGenVertexArrays(1, &m_Id);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_Id);
}

void VertexArray::bind() const {
    glBindVertexArray(m_Id);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}


void VertexArray::addBuffer(const VertexBufferLayout& layout, const VertexBuffer& vb) {
    bind();
    vb.bind();

    const auto& elements = layout.getElements();

    for ( unsigned int i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)m_Offset);

        m_Offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}