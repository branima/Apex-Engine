#pragma once

#include <memory>

#include "circlecollider.h"
#include "math.h"
#include "texture.h"
#include "transform.h"

class GameObject
{
    public:
        GameObject(const Apex::Math::Vec3& position, const Apex::Math::Vec3& scale, float rotation,
                float movementSpeed, const std::shared_ptr<Apex::Texture>& texture);
        ~GameObject() = default;

        virtual void move(){};

        const Apex::Transform& getTransform() const {return m_Transform;}
        Apex::Transform& getTransform() {return m_Transform;}
        Apex::CircleCollider& getCollider() {return m_Collider;}
        const std::shared_ptr<Apex::Texture>& getTexture() const {return m_Texture;}

        float getMovementSpeed() const {return m_MovementSpeed;}
        void setMovementSpeed(float value) {m_MovementSpeed = value;}

        bool getIsMarkedForDestruction() const {return m_IsMarkedForDestruction;}
        void setIsMarkedForDestruction(bool value) {m_IsMarkedForDestruction = value;}

    protected:
        Apex::Transform m_Transform;
        Apex::CircleCollider m_Collider;
        std::shared_ptr<Apex::Texture> m_Texture;

        float m_MovementSpeed{0};

        bool m_IsMarkedForDestruction{false};
};