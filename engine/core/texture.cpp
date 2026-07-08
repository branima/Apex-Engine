#include "texture.h"

#include <glad/glad.h>

#include <iostream>

#include "stb_image.h"

Apex::Texture::Texture(const char* path, bool shouldFlipVerticallyOnLoad)
{
    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, m_ID);

    stbi_set_flip_vertically_on_load(shouldFlipVerticallyOnLoad);

    // set the texture wrapping/filtering options (on currently bound texture)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    // Free the image memory after we're done working with it
    stbi_image_free(data);
}

Apex::Texture::~Texture()
{
    glDeleteTextures(1, &m_ID);
}

Apex::Texture::Texture(Texture&& other) noexcept
{
    m_ID = other.m_ID;
    other.m_ID = 0;
}

Apex::Texture& Apex::Texture::operator=(Texture&& other) noexcept
{
    if (this != &other)
    {
        glDeleteTextures(1, &m_ID);

        m_ID = other.m_ID;
        other.m_ID = 0;
    }

    return *this;
}

void Apex::Texture::bindToTextureUnit(unsigned int unit)
{
    glActiveTexture(unit);
    glBindTexture(GL_TEXTURE_2D, m_ID);
}