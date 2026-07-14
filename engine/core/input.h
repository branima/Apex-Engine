#pragma once

#include "key.h"
#include "math.h"
#include "window.h"

namespace Apex
{
    class Input
    {
        public:
            static unsigned int getGLFWKey(Key key);

            static bool isKeyHeld(Key key);
            static bool isKeyPressed(Key key);
            static bool isKeyReleased(Key key);

            static bool isMouseButtonHeld(Key button);
            static bool isMouseButtonPressed(Key button);
            static bool isMouseButtonReleased(Key button);\

            static Math::Vec2 getCursorPosition(const Window& window);

            static void keyCallback(GLFWwindow* w, int key, int scancode, int action, int mods);
            static void mouseButtonCallback(GLFWwindow* w, int button, int action, int mods);

            static void endFrame();

        private:
            inline static std::array<bool, GLFW_KEY_LAST + 1> ms_KeysHeld;
            inline static std::array<bool, GLFW_KEY_LAST + 1> ms_KeysPressed;
            inline static std::array<bool, GLFW_KEY_LAST + 1> ms_KeysReleased;

            inline static std::array<bool, GLFW_MOUSE_BUTTON_LAST + 1> ms_ButtonsHeld;
            inline static std::array<bool, GLFW_MOUSE_BUTTON_LAST + 1> ms_ButtonsPressed;
            inline static std::array<bool, GLFW_MOUSE_BUTTON_LAST + 1> ms_ButtonsReleased;
    };
}