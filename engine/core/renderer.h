#pragma once

#include "elementbuffer.h"
#include "math.h"
#include "vertexarray.h"

namespace Apex
{
    class Renderer
    {
        public:
            static void initialize();

            static void clearWindowWithColor(const Math::Vec4& color);
            static void clearWindow();

            static void drawElements(VertexArray& vtxArray, const ElementBuffer& elBuffer);

            static void updateOrtographicProjMatrix(unsigned int width, unsigned int height);
            static const Math::Mat4& getOrtographicProjMatrix();

        private:
            static Math::Mat4 ms_OrtogonalProjMatrix;
    };
}