#include "asteroid.h"

#include "renderer.h"
#include "time.h"

#include <iostream>

Asteroid::Asteroid(const Apex::Math::Vec3& position, const Apex::Math::Vec3& scale, float rotation, float movementSpeed, const std::shared_ptr<Apex::Texture>& texture)
{
    m_Transform.setPosition(position);
    m_Transform.setScale(scale);
    m_Transform.setRotation(rotation);
    m_MovementSpeed = movementSpeed;

    m_Texture = texture;
}

void Asteroid::move()
{
    m_Transform.setPosition(m_Transform.getPosition() + m_Transform.getForward() * m_MovementSpeed * Apex::Time::getDeltaTime());
}