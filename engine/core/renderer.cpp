#include "renderer.h"

#include <iostream>

#include <GLFW/glfw3.h>

namespace Apex
{
    Math::Mat4 Renderer::ms_OrtogonalProjMatrix = Math::getIdentity();
}

/* static */ void Apex::Renderer::initialize()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

/* static */ void Apex::Renderer::clearWindowWithColor(const Math::Vec4& color)
{
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT);
}

/* static */ void Apex::Renderer::clearWindow()
{
    clearWindowWithColor(Math::Vec4(0.0));
}

/* static */ void Apex::Renderer::drawElements(VertexArray& vtxArray, const ElementBuffer& elBuffer)
{
    vtxArray.bind();
    glDrawElements(GL_TRIANGLES, elBuffer.getDataCount(), GL_UNSIGNED_INT, 0);
}

/* static */ void Apex::Renderer::updateOrtographicProjMatrix(unsigned int width, unsigned int height)
{
    ms_OrtogonalProjMatrix = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
}

/* static */ const Apex::Math::Mat4& Apex::Renderer::getOrtographicProjMatrix()
{
    return ms_OrtogonalProjMatrix;
}