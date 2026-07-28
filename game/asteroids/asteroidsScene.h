#pragma once

#include <memory>
#include <unordered_set>

#include "debugrenderer.h"
#include "scene.h"
#include "spriterenderer.h"
#include "utils.h"

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
        std::shared_ptr<Apex::Texture> m_ShipTexture = std::make_shared<Apex::Texture>("resources/textures/ship.png");
        std::shared_ptr<Apex::Texture> m_ProjectileTexture = std::make_shared<Apex::Texture>("resources/textures/missile.png");
        std::array<std::shared_ptr<Apex::Texture>, 2> m_AsteroidTextures {std::make_shared<Apex::Texture>("resources/textures/asteroid 1.png"), std::make_shared<Apex::Texture>("resources/textures/asteroid 2.png")};

        Apex::DebugRenderer m_DebugRenderer;
        Apex::SpriteRenderer m_SpriteRenderer;

        // Ship
        Ship m_Ship;
        Apex::Math::Vec3 m_MovementDirection;

        // Projectiles
        std::vector<std::unique_ptr<Projectile>> m_Projectiles;

        // Asteroids
        std::vector<std::unique_ptr<Asteroid>> m_Asteroids;
        float m_LastAsteroidSpawnTime {-1000.0f}; // Forcing immediate spawn on engine startup
        float m_AsteroidSpawnRate {0.35f}; // Asteroids per second.

        std::unordered_set<void*> m_ObjectsForDestruction;

        Apex::Math::Vec2 m_CursorPosition;
};