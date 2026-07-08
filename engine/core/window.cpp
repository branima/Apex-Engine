#include "window.h"

#include <iostream>

static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Apex::Window::Window()
{
    // Initialize GLFW
    glfwInit();

    // Tell GLFW we want OpenGL 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

Apex::Window::Window(int width, int height, const char* title)
    : Window()
{
    // Create window
    m_WindowInstance = glfwCreateWindow(width, height, title, NULL, NULL);
    if (m_WindowInstance == NULL)
    {
        throw std::runtime_error("Failed to create window.");
    }

    glfwMakeContextCurrent(m_WindowInstance);

    // Load OpenGL functions with GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD.");
    }

    // Set viewport
    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(m_WindowInstance, framebufferSizeCallback);
}

Apex::Window::~Window()
{
    glfwDestroyWindow(m_WindowInstance);
    glfwTerminate();
}

bool Apex::Window::getShouldWindowClose() const
{
    return glfwWindowShouldClose(m_WindowInstance);
}

void Apex::Window::setShouldWindowClose(bool value)
{
    glfwSetWindowShouldClose(m_WindowInstance, value);
}

bool Apex::Window::isKeyPressed(int key) const
{
    return glfwGetKey(m_WindowInstance, key) == GLFW_PRESS;
}

void Apex::Window::SwapBuffers()
{
    glfwSwapBuffers(m_WindowInstance);
}

void Apex::Window::PollEvents()
{
        glfwPollEvents();
}