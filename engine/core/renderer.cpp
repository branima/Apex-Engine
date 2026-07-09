#include "renderer.h"

#include <GLFW/glfw3.h>

void Apex::Renderer::clearWindowWithColor(glm::vec4 color)
{
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Apex::Renderer::clearWindow()
{
    clearWindowWithColor(glm::vec4(0.0));
}

void Apex::Renderer::DrawElements(Shader& shader, VertexArray& vtxArray, const ElementBuffer& elBuffer)
{
    shader.use();
    vtxArray.bind();

    glDrawElements(GL_TRIANGLES, elBuffer.getDataCount(), GL_UNSIGNED_INT, 0);
}