#include "projectile.h"

#include "time.h"

Projectile::Projectile(const Apex::Math::Vec3& position, const Apex::Math::Vec3& scale, float rotation, float movementSpeed, const std::shared_ptr<Apex::Texture>& texture)
    : GameObject(position, scale, rotation, movementSpeed, texture)
{
}

void Projectile::move()
{
    m_Transform.setPosition(m_Transform.getPosition() + m_Transform.getForward() * m_MovementSpeed * Apex::Time::getDeltaTime());
}