#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "elementbuffer.h"
#include "shader.h"
#include "vertexarray.h"

namespace Apex
{
    class Renderer
    {
        public:
            Renderer() = default;
            ~Renderer() = default;

            void clearWindowWithColor(glm::vec4 color);
            void clearWindow();

            void DrawElements(Shader& shader, VertexArray& vtxArray, const ElementBuffer& elBuffer);
    };
}