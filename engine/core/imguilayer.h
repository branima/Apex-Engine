#pragma once

#include "window.h"

namespace Apex
{
    class ImGuiLayer
    {
        public:
            static void initialize(const Window& window);
            static void shutdown();

            static void beginFrame();
            static void endFrame();
    };
}
