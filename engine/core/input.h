#pragma once

#include "key.h"
#include "math.h"
#include "window.h"

namespace Apex
{
    class Input
    {
        public:
            static bool isKeyPressed(const Window& window, Key key);
            static unsigned int getGLFWKey(Key key);

            static Math::Vec2 getCursorPosition(const Window& window);
    };
}