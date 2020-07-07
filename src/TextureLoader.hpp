#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <string>

#include "vendor/stb_image/stb_image.h"

class TextureLoader {
public:
    TextureLoader(const std::string& filepath);
    void bind(unsigned int texture_id) const;
    void unbind(unsigned int texture_id) const;

private:
    unsigned int m_Id;
    int m_Width, m_Height, m_NrChannels;
};