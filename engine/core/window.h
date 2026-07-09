#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Apex
{
    class Window
    {
        public:
            Window();
            Window(int width, int height, const char* title);
            ~Window();

            bool getShouldWindowClose() const;
            void setShouldWindowClose(bool value);

            // Input
            bool isKeyPressed(int key) const;

            // Rendering
            void swapBuffers();

            // Eventing
            void pollEvents();

        private:
            GLFWwindow* m_WindowInstance = nullptr;
    };
}