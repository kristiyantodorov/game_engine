#include <iostream>

#include "TextureLoader.hpp"

TextureLoader::TextureLoader(const std::string& filepath) {
    glGenTextures(1, &m_Id);
    glBindTexture(GL_TEXTURE_2D, m_Id);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    
    unsigned char* data;
    data = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_NrChannels, 0);
    if (data)
    {
        unsigned int format;
        if (m_NrChannels == 1)
            format = GL_RED;
        else if (m_NrChannels == 3)
            format = GL_RGB;
        else if (m_NrChannels == 4)
            format = GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void TextureLoader::bind(unsigned int texture_id) const {
    glActiveTexture(texture_id);
    glBindTexture(GL_TEXTURE_2D, m_Id);
}

void TextureLoader::unbind(unsigned int texture_id) const {
    glActiveTexture(texture_id);
    glBindTexture(GL_TEXTURE_2D, 0);
}