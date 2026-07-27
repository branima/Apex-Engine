#include "asteroidsScene.h"

#include "input.h"
#include "renderer.h"

#include <iostream>

AsteroidsScene::AsteroidsScene()
    : m_Ship(Apex::Math::Vec3(getSceneCenter().x, getSceneCenter().y, 1.0f), Apex::Math::Vec3(100.0f, 100.0f, 1.0f), 0.0f, 500.0f),
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

        m_Projectiles.push_back(std::make_unique<Projectile>(projectileSpawnPosition, shipScale / 5.0f, shipTransform.getRotation(), m_Ship.getMovementSpeed() * 2.0f));
    }

    m_CursorPosition = Apex::Input::getCursorPosition(window);

    if (Apex::Input::isKeyPressed(Apex::Key::Escape))
    {
        window.setShouldWindowClose(true);
    }
}

void AsteroidsScene::update()
{
    m_Ship.move(m_MovementDirection);
    m_Ship.lookAt(m_CursorPosition);

    for (auto& projectile : m_Projectiles)
    {
        projectile->move();
    }

    // Projectile is out of screen, destroy it
    std::erase_if(m_Projectiles,
    [this](const std::unique_ptr<Projectile>& projectile)
    {
        return isObjectOutOfScene(projectile->getTransform());
    });
}

void AsteroidsScene::onRender()
{
    Apex::Renderer::clearWindowWithColor(Apex::Math::Vec4(0.1f, 0.1f, 0.1f, 1.0f));

    m_Ship.onRender();
    for (const auto& projectile : m_Projectiles)
    {
        projectile->onRender();
    }
}