#include "elementbuffer.h"

#include <glad/glad.h>

Apex::ElementBuffer::ElementBuffer()
{
    glGenBuffers(1, &m_ID);
}

Apex::ElementBuffer::~ElementBuffer()
{
    glDeleteBuffers(1, &m_ID);
}

Apex::ElementBuffer::ElementBuffer(ElementBuffer&& other) noexcept
{
    m_ID = other.m_ID;
    other.m_ID = 0;
}

Apex::ElementBuffer& Apex::ElementBuffer::operator=(ElementBuffer&& other) noexcept
{
    if (this != &other)
    {
        glDeleteBuffers(1, &m_ID);

        m_ID = other.m_ID;
        other.m_ID = 0;
    }

    return *this;
}

void Apex::ElementBuffer::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void Apex::ElementBuffer::setData(const unsigned int* data, unsigned int dataSize, bool isDataDynamic)
{
    m_DataSize = dataSize;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, isDataDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}