#include "vertexarray.h"

#include <glad/glad.h>

Apex::VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_ID);
}

Apex::VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_ID);
}

Apex::VertexArray::VertexArray(VertexArray&& other) noexcept
{
    m_ID = other.m_ID;
    other.m_ID = 0;
}

Apex::VertexArray& Apex::VertexArray::operator=(VertexArray&& other) noexcept
{
    if (this != &other)
    {
        glDeleteVertexArrays(1, &m_ID);

        m_ID = other.m_ID;
        other.m_ID = 0;
    }

    return *this;
}

void Apex::VertexArray::bind()
{
    glBindVertexArray(m_ID);
}

void Apex::VertexArray::unbind()
{
    glBindVertexArray(0);
}

void Apex::VertexArray::setVertexAttribute(unsigned int location, unsigned int size, unsigned int stride, unsigned long long offset)
{
    glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride, (void*)offset);
    glEnableVertexAttribArray(location);
}