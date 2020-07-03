#include "Triangle.hpp"
#include "VertexArray.hpp"

Triangle::Triangle(const float* vertices) : m_Vertices(vertices) {
}


void Triangle::draw() {
    VertexBuffer vb(m_Vertices, 15 * sizeof(float));
    VertexBufferLayout layout;
    layout.push<float>(3);
    layout.push<float>(2);
    VertexArray va;
    va.addBuffer(layout, vb);
    va.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    va.unbind();
}