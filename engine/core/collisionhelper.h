#pragma once

#include "circlecollider.h"
#include "transform.h"

namespace Apex
{
    class CollisionHelper
    {
        public:
            static bool checkCollision(const CircleCollider& colliderA, const Transform& transformA,
                const CircleCollider& colliderB, const Transform& transformB);
    };
}