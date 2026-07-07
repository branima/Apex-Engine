#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Apex
{
    class Window
    {
        public:
            Window();
            Window(const int width, const int height, const char* title);

            // Utility
            bool isInstanceValid();

            bool getShouldWindowClose();
            void setShouldWindowClose(const bool value);

            // Input
            bool isKeyPressed(int key);

            // Rendering
            void SwapBuffers();

        private:
            GLFWwindow* m_WindowInstance = nullptr;
    };
}