#include "asteroidsScene.h"

#include "collisionhelper.h"
#include "input.h"
#include "renderer.h"
#include "utils.h"

#include <fstream>
#include <iostream>

#include <imgui.h>

AsteroidsScene::AsteroidsScene()
    : m_Ship(Apex::Math::Vec3(getSceneCenter().x, getSceneCenter().y, 1.0f), Apex::Math::Vec3(100.0f, 100.0f, 1.0f), 0.0f, 500.0f, m_ShipTexture),
      m_MovementDirection(0.0f),
      m_State(GameState::Running)
{
    loadHighScore();
}

void AsteroidsScene::handleInputs(Apex::Window& window)
{
    if (Apex::Input::isKeyPressed(Apex::Key::Escape))
    {
        window.setShouldWindowClose(true);
    }

    if (m_State == GameState::Over)
    {
        if (Apex::Input::isKeyPressed(Apex::Key::Space))
        {
            reset();
        }
        return;
    }

    if (Apex::Input::isKeyPressed(Apex::Key::C))
    {
        m_IsGizmoEnabled = !m_IsGizmoEnabled;
    }

    if (Apex::Input::isKeyPressed(Apex::Key::TAB))
    {
        m_IsDebugWindowActive = !m_IsDebugWindowActive;
    }

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
        spawnProjectile();
    }

    m_CursorPosition = Apex::Input::getCursorPosition(window, SCENE_WIDTH, SCENE_HEIGHT);
}

void AsteroidsScene::reset()
{
    Apex::Transform& shipTransform = m_Ship.getTransform();
    shipTransform.setPosition({getSceneCenter().x, getSceneCenter().y, 1.0f});
    shipTransform.setScale({100.0f, 100.0f, 1.0f});
    shipTransform.setRotation(0.0f);

    m_Ship.setMovementSpeed(500.0f);

    m_Projectiles.clear();
    m_Asteroids.clear();

    m_MovementDirection = Apex::Math::Vec3(0.0f);

    m_AsteroidSpawnRate = 0.5f;
    m_LastAsteroidSpawnTime = -1000.0f;

    m_Lives = 3;
    m_LastShipHitTime = -1000.0f;

    m_Score = 0;

    m_State = GameState::Running;

    m_LastGameSpeedUpTime = 0.0f;
    m_SpeedUpPercentage = 0.0f;
}

void AsteroidsScene::update()
{
    if (m_State != GameState::Running)
    {
        return;
    }

    const float currentTime = Apex::Time::getTime();

    objectMove();
    checkOutOfScreenObjects();
    processCollisions(currentTime);

    spawnAsteroids(currentTime);
    removeObjectsQueuedForDestruction();

    progressionStep(currentTime);
}

void AsteroidsScene::onRender()
{
    Apex::Renderer::clearWindowWithColor(Apex::Math::Vec4(0.1f, 0.1f, 0.1f, 1.0f));

    const float currentTime = Apex::Time::getTime();

    /// Ship
    const bool shouldRenderShip = (currentTime - m_LastShipHitTime >= m_ShipInvincibilityTime) || static_cast<int>(currentTime / 0.15f) % 2 == 0;
    if (shouldRenderShip)
    {
        const Apex::Transform& shipTransform = m_Ship.getTransform();
        const Apex::CircleCollider& shipCollider = m_Ship.getCollider();
        m_SpriteRenderer.render(shipTransform, *m_Ship.getTexture());

        if (m_IsGizmoEnabled)
        {
            m_DebugRenderer.drawCircle(shipTransform.getPosition(), shipCollider.getRadius());
        }
    }

    /// Projectiles
    for (const auto& projectile : m_Projectiles)
    {
        const Apex::Transform& projectileTransform = projectile->getTransform();
        const Apex::CircleCollider& projectileCollider = projectile->getCollider();
        m_SpriteRenderer.render(projectileTransform, *projectile->getTexture());

        if (m_IsGizmoEnabled)
        {
            m_DebugRenderer.drawCircle(projectileTransform.getPosition(), projectileCollider.getRadius());
        }
    }

    /// Asteroids
    for (const auto& asteroid : m_Asteroids)
    {
        const Apex::Transform& asteroidTransform = asteroid->getTransform();
        const Apex::CircleCollider& asteroidCollider = asteroid->getCollider();
        m_SpriteRenderer.render(asteroid->getTransform(), *asteroid->getTexture());

        if (m_IsGizmoEnabled)
        {
            m_DebugRenderer.drawCircle(asteroid->getTransform().getPosition(), asteroidCollider.getRadius());
        }
    }

    /// Lives in top left corner
    Apex::Transform lifeTransform = m_Ship.getTransform();
    lifeTransform.setScale(lifeTransform.getScale() * 0.5f);
    lifeTransform.setRotation(0.0f);

    for (int i = 0; i < m_Lives; ++i)
    {
        const float scaleHalf = lifeTransform.getScale().x * 0.5f;
        lifeTransform.setPosition({scaleHalf + i * scaleHalf * 2.5f, scaleHalf, 0.0f});
        m_SpriteRenderer.render(lifeTransform, *m_Ship.getTexture());
    }

    /// Game Over screen
    if (m_State == GameState::Over)
    {
        m_SpriteRenderer.renderAcrossScene(getWidth(), getHeight(), *m_GameOverTexture);
    }
}

void AsteroidsScene::objectMove()
{
    // Ship
    m_Ship.move(m_MovementDirection);
    m_Ship.lookAt(m_CursorPosition);

    // Projectiles
    for (auto& projectile : m_Projectiles)
    {
        projectile->move();
    }

    // Asteroids
    for (auto& asteroid : m_Asteroids)
    {
        asteroid->move();
    }
}

void AsteroidsScene::checkOutOfScreenObjects()
{
    // Projectiles
    for (auto& projectile : m_Projectiles)
    {
        if (isObjectOutOfScene(projectile->getTransform()))
        {
            projectile->setIsMarkedForDestruction(true);
        }
    }

    // Asteroids
    for (auto& asteroid : m_Asteroids)
    {
        if (isObjectOutOfScene(asteroid->getTransform()))
        {
            asteroid->setIsMarkedForDestruction(true);
        }
    }
}

void AsteroidsScene::removeObjectsQueuedForDestruction()
{
    std::erase_if(m_Asteroids,
    [this](const std::unique_ptr<Asteroid>& asteroid)
    {
        return  asteroid->getIsMarkedForDestruction();
    });

    std::erase_if(m_Projectiles,
    [this](const std::unique_ptr<Projectile>& projectile)
    {
        return  projectile->getIsMarkedForDestruction();
    });
}

void AsteroidsScene::spawnAsteroids(float currentTime)
{
    if (currentTime - m_LastAsteroidSpawnTime >= 1.0f / m_AsteroidSpawnRate)
    {
        spawnAsteroid();
        m_LastAsteroidSpawnTime = currentTime;
    }
}

void AsteroidsScene::processCollisions(float currentTime)
{
    Apex::CircleCollider& shipCollider = m_Ship.getCollider();
    const Apex::Transform& shipTransform = m_Ship.getTransform();

    for (auto& asteroid : m_Asteroids)
    {
        Apex::CircleCollider& asteroidCollider = asteroid->getCollider();
        const Apex::Transform& asteroidTransform = asteroid->getTransform();

        if (currentTime - m_LastShipHitTime >= m_ShipInvincibilityTime && Apex::CollisionHelper::checkCollision(shipCollider, shipTransform, asteroidCollider, asteroidTransform))
        {
            if (--m_Lives == 0)
            {
                m_State = GameState::Over;
                saveHighScore();
            }

            m_LastShipHitTime = currentTime;
        }

        for (auto& projectile : m_Projectiles)
        {
            if (projectile->getIsMarkedForDestruction())
            {
                continue;
            }

            Apex::CircleCollider& projectileCollider = projectile->getCollider();
            const Apex::Transform& projectileTransform = projectile->getTransform();

            if (Apex::CollisionHelper::checkCollision(asteroidCollider, asteroidTransform, projectileCollider, projectileTransform))
            {
                asteroid->setIsMarkedForDestruction(true);
                projectile->setIsMarkedForDestruction(true);
                m_Score += getScoreForCategory(asteroid->getCategory());
                break;
            }
        }
    }

    for (auto& asteroid : m_Asteroids)
    {
        if(asteroid->getIsMarkedForDestruction())
        {
            asteroidSplit(*asteroid);
        }
    }

    if (m_AsteroidSplitSpawns.size() > 0)
    {
        std::ranges::move(m_AsteroidSplitSpawns, std::back_inserter(m_Asteroids));
        m_AsteroidSplitSpawns.clear();
    }
}

void AsteroidsScene::asteroidSplit(const Asteroid& asteroid)
{
    const AsteroidCategory category = asteroid.getCategory();
    if (category != AsteroidCategory::Invalid && category != AsteroidCategory::Small)
    {
        const int newAsteroidCount = Apex::Utils::getRandomInt(2, 5);

        const Apex::Transform& ogAsteroidTransform = asteroid.getTransform();
        const Apex::Math::Vec3& spawnPosition = ogAsteroidTransform.getPosition();
        const Apex::Math::Vec3& scale = ogAsteroidTransform.getScale() / static_cast<float>(newAsteroidCount);
        const float initialRotation = ogAsteroidTransform.getRotation();
        const float movementSpeed = asteroid.getMovementSpeed();
        const std::shared_ptr<Apex::Texture>& texture = asteroid.getTexture();

        for (int i = 0; i < newAsteroidCount; ++i)
        {
            const float rotation = initialRotation + Apex::Math::eulerToRadian(i * 360.0f / newAsteroidCount + Apex::Utils::getRandomFloat(-30.0f, 30.0f));
            m_AsteroidSplitSpawns.push_back(std::make_unique<Asteroid>(spawnPosition, scale, rotation, movementSpeed * (1.0f + Apex::Utils::getRandomFloat(0.5f, 1.5f)), texture));
        }
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
    const float movementSpeed = Apex::Utils::getRandomFloat(200.0f, 400.0f) * 100.0f / scaleFactor;

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

void AsteroidsScene::spawnProjectile()
{
    const Apex::Transform& shipTransform = m_Ship.getTransform();
    const Apex::Math::Vec3& shipScale = shipTransform.getScale();
    // We want to spawn projectiles from the tip of the ship, not from the middle of the sprite, hence the offset
    const Apex::Math::Vec3 projectileSpawnPosition = shipTransform.getPosition() + shipTransform.getForward() * shipScale.y / 2.0f;

    m_Projectiles.push_back(std::make_unique<Projectile>(projectileSpawnPosition, shipScale / 5.0f, shipTransform.getRotation(), m_Ship.getMovementSpeed() * 2.0f, m_ProjectileTexture));
}

int AsteroidsScene::getScoreForCategory(AsteroidCategory category) const
{
    // Smaller asteroids are harder to hit, so they're worth more
    switch (category)
    {
    case AsteroidCategory::Small:
        return 100;
    case AsteroidCategory::Medium:
        return 50;
    case AsteroidCategory::Big:
        return 20;
    default:
        return 0;
    }
}

void AsteroidsScene::progressionStep(float currentTime)
{
    if (currentTime - m_LastGameSpeedUpTime >= m_SpeedUpTimer)
    {
        m_SpeedUpPercentage += m_SpeedUpStep;
        m_LastGameSpeedUpTime = currentTime;

        m_AsteroidSpawnRate *= (1.0f + m_SpeedUpPercentage);
        for (auto& asteroid : m_Asteroids)
        {
            asteroid->setMovementSpeed(asteroid->getMovementSpeed() * (1.0f + m_SpeedUpPercentage));
        }
    }
}

void AsteroidsScene::loadHighScore()
{
    std::ifstream file(HIGH_SCORE_FILE);
    if (file.is_open())
    {
        file >> m_HighScore;
    }
}

void AsteroidsScene::saveHighScore()
{
    if (m_Score <= m_HighScore)
    {
        return;
    }

    m_HighScore = m_Score;

    std::ofstream file(HIGH_SCORE_FILE);
    if (file.is_open())
    {
        file << m_HighScore;
    }
    else
    {
        std::cout << "Failed to save high score to " << HIGH_SCORE_FILE << std::endl;
    }
}

void AsteroidsScene::onDebugUI()
{
    if (!m_IsDebugWindowActive)
    {
        return;
    }

    ImGui::Begin("Debug");

    ImGui::Text("Score: %d", m_Score);
    ImGui::Text("High Score: %d", m_HighScore);
    ImGui::Separator();

    ImGui::Text("FPS: %.1f (%.2f ms/frame)", 1.0f / Apex::Time::getDeltaTime(), Apex::Time::getDeltaTime() * 1000.0f);
    ImGui::Text("Asteroids: %zu", m_Asteroids.size());
    ImGui::Text("Projectiles: %zu", m_Projectiles.size());
    ImGui::Text("Speed up percentage (progression) : %.2f", m_SpeedUpPercentage);
    ImGui::Text("Asteroid spawn rate per second : %.2f", m_AsteroidSpawnRate);
    ImGui::Separator();

    ImGui::Checkbox("Show colliders", &m_IsGizmoEnabled);

    ImGui::End();
}