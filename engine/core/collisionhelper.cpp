#include "collisionhelper.h"

/* static */ bool Apex::CollisionHelper::checkCollision(const CircleCollider& colliderA, const Transform& transformA,
        const CircleCollider& colliderB, const Transform& transformB)
{
    const Math::Vec3 colliderCenterA = transformA.getPosition() + colliderA.getOffset();
    const Math::Vec3 colliderCenterB = transformB.getPosition() + colliderB.getOffset();
    const float totalRadius = colliderA.getRadius() + colliderB.getRadius();
    const Math::Vec3 centerDiff = colliderCenterB - colliderCenterA;

    return totalRadius * totalRadius >= Math::dotProduct(centerDiff, centerDiff);
}