#include "demoscene.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cmath>

#include "stb_image.h"

void shapeSetup(unsigned int& VBO, unsigned int& VAO, unsigned int& EBO)
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
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Vertex data buffer setup
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Element buffer setup
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Unbind buffers after usage
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

DemoScene::DemoScene()
{
    m_Texture1 = Apex::Texture("resources/textures/container.jpg");
    m_Texture2 = Apex::Texture("resources/textures/awesomeface.png", true);
    m_Shader = Apex::Shader("shaders/shader.vs", "shaders/shader.fs");

    //Prepare shaders and vertex information before render loop
    shapeSetup(m_VBO, m_VAO, m_EBO);

    m_Shader.use();
    m_Shader.setInt("texture1", 0);
    m_Shader.setInt("texture2", 1);
}

DemoScene::~DemoScene()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

void clearScreenWithColor()
{
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void renderShape(unsigned int& VAO, Apex::Shader& shader, Apex::Texture& texture1, Apex::Texture& texture2)
{
    texture1.bindToTextureUnit(GL_TEXTURE0);
    texture2.bindToTextureUnit(GL_TEXTURE1);

    shader.use();
    glBindVertexArray(VAO);
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
    renderShape(m_VAO, m_Shader, m_Texture1, m_Texture2);
}