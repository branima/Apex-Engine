#pragma once

#include "elementbuffer.h"
#include "math.h"
#include "vertexarray.h"

namespace Apex
{
    class Renderer
    {
        public:
            Renderer() = default;
            ~Renderer() = default;

            void clearWindowWithColor(Math::Vec4 color);
            void clearWindow();

            void drawElements(VertexArray& vtxArray, const ElementBuffer& elBuffer);
    };
}