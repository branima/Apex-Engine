#include "input.h"

#include <GLFW/glfw3.h>

/* static */ bool Apex::Input::isKeyPressed(const Window& window,Key key)
{
    return glfwGetKey(window.getWindowInstance(), getGLFWKey(key)) == GLFW_PRESS;
}

/* static */ unsigned int Apex::Input::getGLFWKey(Key key)
{
    switch (key)
    {
    case Key::W:
        return GLFW_KEY_W;
        break;
    case Key::A:
        return GLFW_KEY_A;
        break;
    case Key::S:
        return GLFW_KEY_S;
        break;
    case Key::D:
        return GLFW_KEY_D;
        break;
    case Key::Space:
        return GLFW_KEY_SPACE;
        break;
    case Key::Escape:
        return GLFW_KEY_ESCAPE;
        break;
    default:
        return GLFW_KEY_UNKNOWN;
        break;
    }
}

/* static */ Apex::Math::Vec2 Apex::Input::getCursorPosition(const Window& window)
{
    double x, y;
    glfwGetCursorPos(window.getWindowInstance(), &x, &y);
    return Math::Vec2(static_cast<float>(x), static_cast<float>(y));
}