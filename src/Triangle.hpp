#include "vendor/glm/glm.hpp"

class Triangle {
public:
    Triangle(const float* vertices);
    void draw();

private:
    const float* m_Vertices;
};