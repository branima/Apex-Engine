#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include "shader.h"

using namespace std;

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void clearScreenWithColor()
{
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void prepareTriangle(unsigned int& VBO, unsigned int& VAO)
{
    float vertices[] = {
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    // Vertex array setup
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Vertex data buffer setup
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind buffers after usage
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void renderTriangle(unsigned int& VAO, Shader& shader)
{
    shader.setFloat("horOffset", 0.25f);
    shader.use();
    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe draw
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Regular draw
    glBindVertexArray(0);
}

int main()
{
    // Initialize GLFW
    glfwInit();

    // Tell GLFW we want OpenGL 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Apex Engine", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Load OpenGL functions with GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    // Set viewport
    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    
    //Prepare shaders and vertex information before render loop
    unsigned int VBO, VAO;
    prepareTriangle(VBO, VAO);
    Shader myShader("shaders/shader.vs", "shaders/shader.fs");

    // Render loop
    while (!glfwWindowShouldClose(window))
    {        
        // Input: escape closes window
        processInput(window);
        
        // Clear screen (dark blue)
        clearScreenWithColor();

        // Render a triangle
        renderTriangle(VAO, myShader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();

    return 0;
}