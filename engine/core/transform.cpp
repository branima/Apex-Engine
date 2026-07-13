#include "transform.h"

Apex::Transform::Transform(const Math::Vec3& position, const Math::Vec3& scale)
    : m_Position(position),
      m_Scale(scale)
{
}