#pragma once

#include <memory>

#include "scene.h"
#include "window.h"

namespace Apex
{
    class Application
    {
        public:
            Application();
            ~Application() = default;

            void run();

        private:
            std::unique_ptr<Window> m_WindowInstance;
            std::unique_ptr<Scene> m_CurrentScene;
    };
}