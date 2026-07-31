#pragma once

#include "gameobject.h"

class Projectile : public GameObject
{
    public:
        Projectile(const Apex::Math::Vec3& position, const Apex::Math::Vec3& scale, float rotation, float movementSpeed, const std::shared_ptr<Apex::Texture>& texture);
        ~Projectile() = default;

        void move() override;
};