#include "asteroid.h"

#include "time.h"

Asteroid::Asteroid(const Apex::Math::Vec3& position, const Apex::Math::Vec3& scale, float rotation, float movementSpeed, const std::shared_ptr<Apex::Texture>& texture)
    : GameObject(position, scale, rotation, movementSpeed, texture)
{
    if (scale.x < 100.0f)
    {
        m_Category = AsteroidCategory::Small;
    }
    else if (scale.x < 300.0f)
    {
        m_Category = AsteroidCategory::Medium;
    }
    else
    {
        m_Category = AsteroidCategory::Big;
    }
}

void Asteroid::move()
{
    m_Transform.setPosition(m_Transform.getPosition() + m_Transform.getForward() * m_MovementSpeed * Apex::Time::getDeltaTime());
}