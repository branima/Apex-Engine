#include "asteroidsScene.h"

#include "input.h"
#include "renderer.h"

AsteroidsScene::AsteroidsScene()
    : m_Ship(Apex::Math::Vec3(getSceneCenter().x, getSceneCenter().y, 1.0f), Apex::Math::Vec3(100.0f, 100.0f, 1.0f), 0.0f, 500.0f),
      m_MovementDirection(0.0f)
{
}

void AsteroidsScene::handleInputs(Apex::Window& window)
{
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

    if (Apex::Input::isKeyPressed(Apex::Key::Escape))
    {
        window.setShouldWindowClose(true);
    }

    m_CursorPosition = Apex::Input::getCursorPosition(window);
}

void AsteroidsScene::update()
{
    m_Ship.move(m_MovementDirection);
    m_Ship.lookAt(m_CursorPosition);
}

void AsteroidsScene::onRender()
{
    Apex::Renderer::clearWindowWithColor(Apex::Math::Vec4(0.1f, 0.1f, 0.1f, 1.0f));

    m_Ship.onRender();
}