#pragma once

#include "math.h"

namespace Apex
{
    class CircleCollider
    {
        public:
            CircleCollider() = default;
            CircleCollider(const Math::Vec3& offset, float radius);
            ~CircleCollider() = default;

            void setOffset(const Math::Vec3& value) {m_Offset = value;}
            const Math::Vec3& getOffset() const {return m_Offset;}
            void setRadius(float value) {m_Radius = value;}
            float getRadius() const {return m_Radius;}

            void setIsCurrentlyInCollision(bool value) {m_IsCurrentlyInCollision = value;}
            bool getIsCurrentlyInCollision() const {return m_IsCurrentlyInCollision;}

        private:
            Math::Vec3 m_Offset{0.0f};
            float m_Radius{0.0f};

            bool m_IsCurrentlyInCollision{false};
    };
}