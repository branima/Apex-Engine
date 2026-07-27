#pragma once

#include "math.h"
#include "texture.h"
#include "transform.h"

#include <memory>

class Projectile
{
    public:
        Projectile(const Apex::Math::Vec3& position, const Apex::Math::Vec3& scale, float rotation, float movementSpeed, const std::shared_ptr<Apex::Texture>& texture);
        ~Projectile() = default;

        void move();

        void setMovementSpeed(float value) {m_MovementSpeed = value;}
        float getMovementSpeed() const {return m_MovementSpeed;}

        const Apex::Transform& getTransform() const {return m_Transform;}
        const Apex::Texture& getTexture() const {return *m_Texture;}

    private:
        Apex::Transform m_Transform;
        std::shared_ptr<Apex::Texture> m_Texture;

    float m_MovementSpeed{0};
};