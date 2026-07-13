#pragma once

#include "elementbuffer.h"
#include "math.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include "vertexarray.h"
#include "vertexbuffer.h"

class Ship
{
    public:
        Ship();
        Ship(const Apex::Math::Vec3& position, const Apex::Math::Vec3& scale);
        ~Ship() = default;

        void onRender();

    private:
        Apex::VertexBuffer m_VtxBuffer;
        Apex::ElementBuffer m_ElBuffer;
        Apex::VertexArray m_VtxArray;

        Apex::Texture m_Texture;
        Apex::Shader m_Shader;

        Apex::Transform m_Transform;
};