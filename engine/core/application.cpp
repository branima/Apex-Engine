#include "application.h"

#include "input.h"
#include "renderer.h"

#include "asteroidsScene.h"

//#include "demoscene.h"

Apex::Application::Application()
{
    m_WindowInstance = std::make_unique<Apex::Window>(AsteroidsScene::SCENE_WIDTH, AsteroidsScene::SCENE_HEIGHT, "Apex Engine");
    //m_CurrentScene = std::make_unique<DemoScene>();
    m_CurrentScene = std::make_unique<AsteroidsScene>();

    Renderer::initialize();
}

void Apex::Application::run()
{
    while (!m_WindowInstance->getShouldWindowClose())
    {
        Time::update();
        m_WindowInstance->pollEvents();

        m_CurrentScene->handleInputs(*m_WindowInstance);

        m_CurrentScene->update();
        m_CurrentScene->onRender();

        m_WindowInstance->swapBuffers();
        Input::endFrame();
    }
}