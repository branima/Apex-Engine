#pragma once

#include "asteroidcategory.h"
#include "gameobject.h"

class Asteroid : public GameObject
{
    public:
        Asteroid(const Apex::Math::Vec3& position, const Apex::Math::Vec3& scale, float rotation, float movementSpeed, const std::shared_ptr<Apex::Texture>& texture);
        ~Asteroid() = default;

        void move() override;

        AsteroidCategory getCategory() const {return m_Category;}

    private:
        AsteroidCategory m_Category{AsteroidCategory::Invalid};
};