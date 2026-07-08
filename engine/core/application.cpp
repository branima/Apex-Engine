#include "application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cmath>

#include "stb_image.h"
#include "shader.h"

#include "texture.h"

Apex::Application::Application()
{
    m_WindowInstance = std::make_unique<Apex::Window>(800, 600, "Apex Engine");
}

void processInput(Apex::Window& window)
{
    if (window.isKeyPressed(GLFW_KEY_ESCAPE))
    {
        window.setShouldWindowClose(true);
    }
}

void clearScreenWithColor()
{
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

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

void renderShape(unsigned int& VAO, Apex::Shader& shader, Apex::Texture& texture1, Apex::Texture& texture2)
{
    texture1.bindToTextureUnit(GL_TEXTURE0);
    texture2.bindToTextureUnit(GL_TEXTURE1);

    shader.use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Apex::Application::run()
{
    //Prepare shaders and vertex information before render loop
    unsigned int VBO, VAO, EBO;
    shapeSetup(VBO, VAO, EBO);

    Texture texture1("resources/textures/container.jpg");
    Texture texture2("resources/textures/awesomeface.png", true);

    Shader myShader("shaders/shader.vs", "shaders/shader.fs");
    myShader.use();
    myShader.setInt("texture1", 0);
    myShader.setInt("texture2", 1);

    // Render loop
    while (!m_WindowInstance->getShouldWindowClose())
    {
        // Input: escape closes window
        processInput(*m_WindowInstance);

        // Clear screen (dark blue)
        clearScreenWithColor();

        // Render a triangle
        renderShape(VAO, myShader, texture1, texture2);

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        unsigned int transformLoc = glGetUniformLocation(myShader.m_ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        m_WindowInstance->SwapBuffers();
        m_WindowInstance->PollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}