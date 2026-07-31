#include "gameobject.h"

GameObject::GameObject(const Apex::Math::Vec3& position, const Apex::Math::Vec3& scale, float rotation,
                float movementSpeed, const std::shared_ptr<Apex::Texture>& texture)
    : m_Transform(position, scale, rotation),
    m_MovementSpeed(movementSpeed),
    m_Texture(texture)
{
    m_Collider.setRadius(scale.x / 2.0f);
}