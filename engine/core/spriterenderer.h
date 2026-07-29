#pragma once

#include "elementbuffer.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include "vertexarray.h"
#include "vertexbuffer.h"

namespace Apex
{
    class SpriteRenderer
    {
    public:
        SpriteRenderer();
        ~SpriteRenderer() = default;

        void render(const Transform& transform, const Texture& texture);
        void renderAcrossScene(float width, float height, const Texture& texture);

    private:
        VertexBuffer m_VtxBuffer;
        ElementBuffer m_ElBuffer;
        VertexArray m_VtxArray;
        Shader m_Shader;
    };
}