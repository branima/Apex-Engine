#include "application.h"

#include "input.h"
#include "renderer.h"

#include "asteroidsScene.h"

//#include "demoscene.h"

Apex::Application::Application()
{
    m_WindowInstance = std::make_unique<Apex::Window>(1200, 800, "Apex Engine");
    //m_CurrentScene = std::make_unique<DemoScene>();
    m_CurrentScene = std::make_unique<AsteroidsScene>();

    Renderer::initialize();
}

void Apex::Application::run()
{
    while (!m_WindowInstance->getShouldWindowClose())
    {
        // Close the window on escape
        if (Apex::Input::isKeyPressed(*m_WindowInstance, Apex::Key::Escape))
        {
            m_WindowInstance->setShouldWindowClose(true);
        }

        m_CurrentScene->onRender();

        m_WindowInstance->swapBuffers();
        m_WindowInstance->pollEvents();
    }
}