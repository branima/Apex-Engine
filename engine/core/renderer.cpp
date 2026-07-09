#include "renderer.h"

#include <GLFW/glfw3.h>

void Apex::Renderer::clearWindowWithColor(Math::Vec4 color)
{
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Apex::Renderer::clearWindow()
{
    clearWindowWithColor(Math::Vec4(0.0));
}

void Apex::Renderer::drawElements(VertexArray& vtxArray, const ElementBuffer& elBuffer)
{
    vtxArray.bind();
    glDrawElements(GL_TRIANGLES, elBuffer.getDataCount(), GL_UNSIGNED_INT, 0);
}