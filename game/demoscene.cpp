#include "demoscene.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cmath>

#include "stb_image.h"

void shapeSetup(Apex::VertexArray& vtxArray, Apex::VertexBuffer& vtxBuffer, Apex::ElementBuffer& elBuffer)
{
    float vertices[] = {
        // positions // colors // texture coords
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    // Vertex array setup
    vtxArray.bind();

    // Vertex data buffer setup
    vtxBuffer.bind();
    vtxBuffer.setData(vertices, sizeof(vertices));

    // Element buffer setup
    elBuffer.bind();
    elBuffer.setData(indices, sizeof(indices));

    // Position attribute
    vtxArray.setVertexAttribute(0, 3, 8 * sizeof(float), 0);

    // Color attribute
    vtxArray.setVertexAttribute(1, 3, 8 * sizeof(float), 3 * sizeof(float));

    // Texture attribute
    vtxArray.setVertexAttribute(2, 2, 8 * sizeof(float), 6 * sizeof(float));

    // Unbind buffers and arrays after usage
    vtxBuffer.unbind();
    vtxArray.unbind();
}

DemoScene::DemoScene()
{
    m_VtxArray = Apex::VertexArray();
    m_VtxBuffer = Apex::VertexBuffer();
    m_ElBuffer = Apex::ElementBuffer();

    m_Texture1 = Apex::Texture("resources/textures/container.jpg");
    m_Texture2 = Apex::Texture("resources/textures/awesomeface.png", true);
    m_Shader = Apex::Shader("shaders/shader.vs", "shaders/shader.fs");

    //Prepare shaders and vertex information before render loop
    shapeSetup(m_VtxArray, m_VtxBuffer, m_ElBuffer);

    m_Shader.use();
    m_Shader.setInt("texture1", 0);
    m_Shader.setInt("texture2", 1);
}

void clearScreenWithColor()
{
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void renderShape(Apex::VertexArray& vtxArray, Apex::Shader& shader, Apex::Texture& texture1, Apex::Texture& texture2)
{
    texture1.bindToTextureUnit(GL_TEXTURE0);
    texture2.bindToTextureUnit(GL_TEXTURE1);

    shader.use();
    vtxArray.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void DemoScene::OnRender()
{
    // Clear screen (dark blue)
    clearScreenWithColor();

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
    trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    m_Shader.setMat4("transform", trans);

    // Render a triangle
    renderShape(m_VtxArray, m_Shader, m_Texture1, m_Texture2);
}