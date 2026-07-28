#include "asteroidsScene.h"

#include "collisionhelper.h"
#include "input.h"
#include "renderer.h"
#include "utils.h"

#include <iostream>

AsteroidsScene::AsteroidsScene()
    : m_Ship(Apex::Math::Vec3(getSceneCenter().x, getSceneCenter().y, 1.0f), Apex::Math::Vec3(100.0f, 100.0f, 1.0f), 0.0f, 500.0f, m_ShipTexture),
      m_MovementDirection(0.0f)
{
}

void AsteroidsScene::handleInputs(Apex::Window& window)
{
    // Movement
    Apex::Math::Vec3 direction(0.0f);
    if (Apex::Input::isKeyHeld(Apex::Key::W))
    {
        direction.y -= 1.0f;
    }
    if (Apex::Input::isKeyHeld(Apex::Key::A))
    {
        direction.x -= 1.0f;
    }
    if (Apex::Input::isKeyHeld(Apex::Key::S))
    {
        direction.y += 1.0f;
    }
    if (Apex::Input::isKeyHeld(Apex::Key::D))
    {
        direction.x += 1.0f;
    }

    m_MovementDirection = direction;

    // Shooting
    if (Apex::Input::isMouseButtonPressed(Apex::Key::MouseLeftClick))
    {
        const Apex::Transform& shipTransform = m_Ship.getTransform();
        const Apex::Math::Vec3& shipScale = shipTransform.getScale();
        // We want to spawn projectiles from the tip of the ship, not from the middle of the sprite, hence the offset
        const Apex::Math::Vec3 projectileSpawnPosition = shipTransform.getPosition() + shipTransform.getForward() * shipScale.y / 2.0f;

        m_Projectiles.push_back(std::make_unique<Projectile>(projectileSpawnPosition, shipScale / 5.0f, shipTransform.getRotation(), m_Ship.getMovementSpeed() * 2.0f, m_ProjectileTexture));
    }

    m_CursorPosition = Apex::Input::getCursorPosition(window);

    if (Apex::Input::isKeyPressed(Apex::Key::Escape))
    {
        window.setShouldWindowClose(true);
    }
}

void AsteroidsScene::update()
{
    // Ship
    m_Ship.move(m_MovementDirection);
    m_Ship.lookAt(m_CursorPosition);

    // Projectiles
    for (auto& projectile : m_Projectiles)
    {
        projectile->move();
    }

    std::erase_if(m_Projectiles,
    [this](const std::unique_ptr<Projectile>& projectile)
    {
        return isObjectOutOfScene(projectile->getTransform());
    });

    // Asteroids
    const float currentTime = Apex::Time::getTime();
    if (currentTime - m_LastAsteroidSpawnTime >= 1.0f / m_AsteroidSpawnRate)
    {
        spawnAsteroid();
        m_LastAsteroidSpawnTime = currentTime;
    }

    for (auto& asteroid : m_Asteroids)
    {
        asteroid->move();
    }

    std::erase_if(m_Asteroids,
    [this](const std::unique_ptr<Asteroid>& asteroid)
    {
        return isObjectOutOfScene(asteroid->getTransform());
    });

    //Collisions
    Apex::CircleCollider& shipCollider = m_Ship.getCollider();
    const Apex::Transform& shipTransform = m_Ship.getTransform();
    bool hasShipCollided = false;

    for (auto& asteroid : m_Asteroids)
    {
        Apex::CircleCollider& asteroidCollider = asteroid->getCollider();
        asteroidCollider.setIsCurrentlyInCollision(false);

        const Apex::Transform& asteroidTransform = asteroid->getTransform();

        if (Apex::CollisionHelper::checkCollision(shipCollider, shipTransform, asteroidCollider, asteroidTransform))
        {
            hasShipCollided = true;
            asteroidCollider.setIsCurrentlyInCollision(true);
        }

        for (auto& projectile : m_Projectiles)
        {
            Apex::CircleCollider& projectileCollider = projectile->getCollider();
            const Apex::Transform& projectileTransform = projectile->getTransform();
            if (Apex::CollisionHelper::checkCollision(asteroidCollider, asteroidTransform, projectileCollider, projectileTransform))
            {
                asteroidCollider.setIsCurrentlyInCollision(true);
                projectileCollider.setIsCurrentlyInCollision(true);
                m_ObjectsForDestruction.insert(asteroid.get());
                m_ObjectsForDestruction.insert(projectile.get());
                break;
            }
        }
    }

    shipCollider.setIsCurrentlyInCollision(hasShipCollided);

    // Destroy asteroids and projectiles that have participated in a collision
    std::erase_if(m_Asteroids,
    [this](const std::unique_ptr<Asteroid>& asteroid)
    {
        return  m_ObjectsForDestruction.contains(asteroid.get());
    });

    std::erase_if(m_Projectiles,
    [this](const std::unique_ptr<Projectile>& projectile)
    {
        return  m_ObjectsForDestruction.contains(projectile.get());
    });

    m_ObjectsForDestruction.clear();
}

void AsteroidsScene::onRender()
{
    Apex::Renderer::clearWindowWithColor(Apex::Math::Vec4(0.1f, 0.1f, 0.1f, 1.0f));

    const Apex::Transform& shipTransform = m_Ship.getTransform();
    const Apex::CircleCollider& shipCollider = m_Ship.getCollider();
    const Apex::Math::Vec4& colliderColor = shipCollider.getIsCurrentlyInCollision() ? Apex::DebugRenderer::COLLIDER_COLOR_COLLIDED : Apex::DebugRenderer::COLLIDER_COLOR_NORMAL;
    m_SpriteRenderer.render(shipTransform, m_Ship.getTexture());
    m_DebugRenderer.drawCircle(shipTransform.getPosition(), m_Ship.getCollider().getRadius(), colliderColor);

    for (const auto& projectile : m_Projectiles)
    {
        m_SpriteRenderer.render(projectile->getTransform(), projectile->getTexture());
        m_DebugRenderer.drawCircle(projectile->getTransform().getPosition(), projectile->getCollider().getRadius());
    }

    for (const auto& asteroid : m_Asteroids)
    {
        const Apex::Transform& asteroidTransform = asteroid->getTransform();
        const Apex::CircleCollider& asteroidCollider = asteroid->getCollider();
        const Apex::Math::Vec4& astColliderColor = asteroidCollider.getIsCurrentlyInCollision() ? Apex::DebugRenderer::COLLIDER_COLOR_COLLIDED : Apex::DebugRenderer::COLLIDER_COLOR_NORMAL;
        m_SpriteRenderer.render(asteroid->getTransform(), asteroid->getTexture());
        m_DebugRenderer.drawCircle(asteroid->getTransform().getPosition(), asteroid->getCollider().getRadius(), astColliderColor);
    }
}

void AsteroidsScene::spawnAsteroid()
{
    // Scale
    const float scaleFactor = Apex::Utils::getRandomFloat(100.0f, 500.0f);
    const Apex::Math::Vec3 scale(scaleFactor);
    // Rotation
    const float rotation = Apex::Math::eulerToRadian(Apex::Utils::getRandomFloat(0.0f, 360.0f));
    // Movement speed
    const float movementSpeed = Apex::Utils::getRandomFloat(50.0f, 150.0f);

    // Spawn Position
    const float x = Apex::Utils::getRandomFloat(0.0f, SCENE_WIDTH);
    const float y = Apex::Utils::getRandomFloat(0.0f, SCENE_HEIGHT);
    const float rotationAngle = rotation + Apex::Math::eulerToRadian(90.0f);
    const Apex::Math::Vec3 directionToEdge(cos(rotationAngle), std::sin(rotationAngle), 0.0f);

    float distanceToHorizontalEdge = std::numeric_limits<float>::infinity();
    float distanceToVerticalEdge = std::numeric_limits<float>::infinity();
    if (std::abs(directionToEdge.x) > Apex::Math::EPSILON)
    {
        distanceToHorizontalEdge = directionToEdge.x > 0.0f ? (SCENE_WIDTH + scaleFactor / 2.0f - x) / directionToEdge.x : (-scaleFactor / 2.0f - x) / directionToEdge.x;
    }
    if (std::abs(directionToEdge.y) > Apex::Math::EPSILON)
    {
        distanceToVerticalEdge = directionToEdge.y > 0.0f ? (SCENE_HEIGHT + scaleFactor / 2.0f - y) / directionToEdge.y : (-scaleFactor / 2.0f - y) / directionToEdge.y;
    }

    const float k = std::min(distanceToHorizontalEdge, distanceToVerticalEdge);
    const Apex::Math::Vec3 position(x + directionToEdge.x * k, y + directionToEdge.y * k, 0.0f);

    m_Asteroids.push_back(std::make_unique<Asteroid>(position, scale, rotation, movementSpeed, m_AsteroidTextures[Apex::Utils::getRandomInt(0, m_AsteroidTextures.size() - 1)]));
}