#pragma once

#include "math.h"

namespace Apex
{
    class Transform
    {
        public:
            Transform();
            Transform(const Math::Vec3& position, const Math::Vec3& scale, float rotation);
            ~Transform() = default;

            void setPosition(const Math::Vec3& value) {m_Position = value;}
            const Math::Vec3& getPosition() const {return m_Position;}

            void setScale(const Math::Vec3& value) {m_Scale = value;}
            const Math::Vec3& getScale() const {return m_Scale;}

            void setRotation(float value) {m_Rotation = value;}
            float getRotation() const {return m_Rotation;}

            Math::Mat4 getMatrix() const;

        private:
            Math::Vec3 m_Position;
            Math::Vec3 m_Scale;
            float m_Rotation{0.0f}; // in radians
    };
}