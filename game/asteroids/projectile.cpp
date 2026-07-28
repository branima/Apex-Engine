#include "projectile.h"

#include "time.h"

Projectile::Projectile(const Apex::Math::Vec3& position, const Apex::Math::Vec3& scale, float rotation, float movementSpeed, const std::shared_ptr<Apex::Texture>& texture)
{
    m_Transform.setPosition(position);
    m_Transform.setScale(scale);
    m_Transform.setRotation(rotation);
    m_MovementSpeed = movementSpeed;

    m_Collider.setRadius(scale.x / 2.0f);

    m_Texture = texture;
}

void Projectile::move()
{
    m_Transform.setPosition(m_Transform.getPosition() + m_Transform.getForward() * m_MovementSpeed * Apex::Time::getDeltaTime());
}