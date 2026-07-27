#pragma once

#include <memory>

#include "scene.h"

#include "asteroid.h"
#include "ship.h"
#include "projectile.h"

class AsteroidsScene : public Apex::Scene
{
    public:
        AsteroidsScene();
        ~AsteroidsScene() = default;

        void handleInputs(Apex::Window& window) override;
        void update() override;
        void onRender() override;

        void spawnAsteroid();

        static constexpr float SCENE_WIDTH = 1200.0f;
        static constexpr float SCENE_HEIGHT = 800.0f;

        float getWidth() const override
        {
            return SCENE_WIDTH;
        }

        float getHeight() const override
        {
            return SCENE_HEIGHT;
        }

    private:
        // Ship
        Ship m_Ship;
        Apex::Math::Vec3 m_MovementDirection;

        // Projectiles
        std::vector<std::unique_ptr<Projectile>> m_Projectiles;

        // Asteroids
        std::vector<std::unique_ptr<Asteroid>> m_Asteroids;
        float m_LastAsteroidSpawnTime {-1000.0f}; // Forcing immediate spawn on engine startup
        float m_AsteroidSpawnRate {0.35f}; // Asteroids per second.

        Apex::Math::Vec2 m_CursorPosition;
};