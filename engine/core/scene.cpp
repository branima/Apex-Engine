#include "scene.h"

bool Apex::Scene::isObjectOutOfScene(const Transform& transform) const
{
    const Apex::Math::Vec3 objPosition = transform.getPosition();
    const Apex::Math::Vec3 objScale = transform.getScale();

    const float halfWidth = objScale.x * 0.5f;
    const float halfHeight = objScale.y * 0.5f;

    return !(objPosition.x >= -halfWidth && objPosition.x <= getWidth() + halfWidth && objPosition.y >= -halfHeight && objPosition.y <= getHeight() + halfHeight);
}

Apex::Math::Vec2 Apex::Scene::getSceneCenter() const
{
    return {getWidth() * 0.5f, getHeight() * 0.5f};
}