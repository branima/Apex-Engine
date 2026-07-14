#include "input.h"

#include <GLFW/glfw3.h>

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

/* static */  bool Apex::Input::isKeyHeld(Key key) { return ms_KeysHeld[getGLFWKey(key)]; }
/* static */  bool Apex::Input::isKeyPressed(Key key) { return ms_KeysPressed[getGLFWKey(key)]; }
/* static */  bool Apex::Input::isKeyReleased(Key key) { return ms_KeysReleased[getGLFWKey(key)]; }

/* static */  bool Apex::Input::isMouseButtonHeld(Key button) { return ms_ButtonsHeld[getGLFWKey(button)]; }
/* static */  bool Apex::Input::isMouseButtonPressed(Key button) { return ms_ButtonsPressed[getGLFWKey(button)]; }
/* static */  bool Apex::Input::isMouseButtonReleased(Key button) { return ms_ButtonsReleased[getGLFWKey(button)]; }

/* static */ void Apex::Input::keyCallback(GLFWwindow* w, int key, int scancode, int action, int mods)
{
    if (key < 0 || key > GLFW_KEY_LAST)
    {
        return;
    }

    if (action == GLFW_PRESS)
    {
        ms_KeysHeld[key] = true;
        ms_KeysPressed[key] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        ms_KeysHeld[key] = false;
        ms_KeysReleased[key] = true;
    }
}

/* static */ void Apex::Input::mouseButtonCallback(GLFWwindow* w, int button, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        ms_ButtonsHeld[button] = true;
        ms_ButtonsPressed[button] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        ms_ButtonsHeld[button] = false;
        ms_ButtonsReleased[button] = true;
    }
}

/* static */ void Apex::Input::endFrame()
{
    ms_KeysPressed.fill(false);
    ms_KeysReleased.fill(false);
    ms_ButtonsPressed.fill(false);
    ms_ButtonsReleased.fill(false);
}