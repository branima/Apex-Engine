#pragma once

#include "key.h"
#include "window.h"

namespace Apex
{
    class Input
    {
        public:
            static bool isKeyPressed(const Window& window, Key key);
            static unsigned int getGLFWKey(Key key);
    };
}