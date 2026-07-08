#include "vertexbuffer.h"

#include <glad/glad.h>

Apex::VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &m_ID);
}

Apex::VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_ID);
}

Apex::VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
{
    m_ID = other.m_ID;
    other.m_ID = 0;
}

Apex::VertexBuffer& Apex::VertexBuffer::operator=(VertexBuffer&& other) noexcept
{
    if (this != &other)
    {
        glDeleteBuffers(1, &m_ID);

        m_ID = other.m_ID;
        other.m_ID = 0;
    }

    return *this;
}

void Apex::VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void Apex::VertexBuffer::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Apex::VertexBuffer::setData(const float* data, int dataSize, bool isDataDynamic)
{
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, isDataDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}