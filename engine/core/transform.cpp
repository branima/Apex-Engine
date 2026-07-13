#include "transform.h"

Apex::Transform::Transform()
  : m_Position(Math::Vec3(0.0f)),
    m_Scale(Math::Vec3(1.0f)),
    m_Rotation(0.0f)
{

}

Apex::Transform::Transform(const Math::Vec3& position, const Math::Vec3& scale, float rotation)
    : m_Position(position),
      m_Scale(scale),
      m_Rotation(rotation)
{
}

Apex::Math::Mat4 Apex::Transform::getMatrix() const
{
  Apex::Math::Mat4 trans = Apex::Math::getIdentity();
  trans = Apex::Math::translate(trans, m_Position);
  trans = Apex::Math::rotate(trans, m_Rotation, Apex::Math::getK());
  trans = Apex::Math::scale(trans, m_Scale);

  return trans;
}