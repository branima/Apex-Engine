#pragma once

#include "gameobject.h"

class Ship : public GameObject
{
    public:
        Ship(const Apex::Math::Vec3& position, const Apex::Math::Vec3& scale, float rotation, float movementSpeed, const std::shared_ptr<Apex::Texture>& texture);

        void move(const Apex::Math::Vec3& direction);
        void lookAt(const Apex::Math::Vec2& cursorPosition);
};