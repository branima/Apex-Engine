#include "window.h"

#include <iostream>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

Apex::Window::Window()
{
    // Initialize GLFW
    glfwInit();

    // Tell GLFW we want OpenGL 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

Apex::Window::Window(const int width, const int height, const char* title)
{
    Window();

    // Create window
    m_WindowInstance = glfwCreateWindow(width, height, title, NULL, NULL);
    if (m_WindowInstance == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_WindowInstance);

    // Load OpenGL functions with GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    // Set viewport
    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(m_WindowInstance, framebufferSizeCallback);
}

bool Apex::Window::isInstanceValid()
{
    return m_WindowInstance != NULL;
}

bool Apex::Window::getShouldWindowClose()
{
    return glfwWindowShouldClose(m_WindowInstance);
}

void Apex::Window::setShouldWindowClose(const bool value)
{
    glfwSetWindowShouldClose(m_WindowInstance, value);
}

bool Apex::Window::isKeyPressed(int key)
{
    return glfwGetKey(m_WindowInstance, key) == GLFW_PRESS;
}

void Apex::Window::SwapBuffers()
{
    glfwSwapBuffers(m_WindowInstance);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}