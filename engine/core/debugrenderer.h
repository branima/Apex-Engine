#pragma once

#include "vertexarray.h"
#include "vertexbuffer.h"
#include "shader.h"

namespace Apex
{
    class DebugRenderer
    {
    public:
        static constexpr Math::Vec4 COLLIDER_COLOR_NORMAL = Math::Vec4(0.0f, 1.0f, 0.0f, 1.0f);
        static constexpr Math::Vec4 COLLIDER_COLOR_COLLIDED = Math::Vec4(1.0f, 0.0f, 0.0f, 1.0f);

        DebugRenderer();
        ~DebugRenderer() = default;

        void drawCircle(const Math::Vec3& center, float radius, const Math::Vec4& color = Math::Vec4(0.0f, 1.0f, 0.0f, 1.0f));

    private:
        const unsigned int CIRCLE_VERTEX_COUNT{32};
        VertexArray m_CircleVertexArray;
        VertexBuffer m_CircleVertexBuffer;
        Shader m_LineShader;
    };
}