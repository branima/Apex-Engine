#include "ship.h"

#include "time.h"

Ship::Ship(const Apex::Math::Vec3& position, const Apex::Math::Vec3& scale, float rotation, float movementSpeed, const std::shared_ptr<Apex::Texture>& texture)
    : GameObject(position, scale, rotation, movementSpeed, texture)
{
}

void Ship::move(const Apex::Math::Vec3& direction)
{
    const Apex::Math::Vec3& oldPosition = m_Transform.getPosition();
    m_Transform.setPosition(oldPosition + Apex::Math::normalize(direction) * m_MovementSpeed * Apex::Time::getDeltaTime());
}

void Ship::lookAt(const Apex::Math::Vec2& cursorPosition)
{
    const Apex::Math::Vec3& position = m_Transform.getPosition();
    Apex::Math::Vec2 toCursor = cursorPosition - Apex::Math::Vec2(position.x, position.y);
    m_Transform.setRotation(std::atan2(toCursor.y, toCursor.x) + Apex::Math::eulerToRadian(90.0f)); // Ships forward is not +X, but -Y, so we have to readjust angle
}