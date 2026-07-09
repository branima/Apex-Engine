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

            GLFWwindow* getWindowInstance() const {return m_WindowInstance;}

            bool getShouldWindowClose() const;
            void setShouldWindowClose(bool value);

            // Rendering
            void swapBuffers();

            // Eventing
            void pollEvents();

        private:
            GLFWwindow* m_WindowInstance = nullptr;
    };
}