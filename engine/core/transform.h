#pragma once

#include "math.h"

namespace Apex
{
    class Transform
    {
        public:
            Transform() = default;
            Transform(const Math::Vec3& position, const Math::Vec3& scale);
            ~Transform() = default;

            void setPosition(const Math::Vec3& value) {m_Position = value;}
            const Math::Vec3& getPosition() const {return m_Position;}

            void setScale(const Math::Vec3& value) {m_Scale = value;}
            const Math::Vec3& getScale() const {return m_Scale;}

        private:
            Math::Vec3 m_Position;
            Math::Vec3 m_Scale;
    };
}