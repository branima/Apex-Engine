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
        Ship(const Apex::Math::Vec3& position, const Apex::Math::Vec3& scale, float rotation, float movementSpeed);
        ~Ship() = default;

        void onRender();

        void move(const Apex::Math::Vec3& direction);
        void lookAt(const Apex::Math::Vec2& cursorPosition);

        void setMovementSpeed(float value) {m_MovementSpeed = value;}
        float getMovementSpeed() const {return m_MovementSpeed;}

    private:
        Apex::VertexBuffer m_VtxBuffer;
        Apex::ElementBuffer m_ElBuffer;
        Apex::VertexArray m_VtxArray;

        Apex::Texture m_Texture;
        Apex::Shader m_Shader;

        Apex::Transform m_Transform;

        float m_MovementSpeed{0};
};