#include "application.h"

#include "demoscene.h"
#include "input.h"

Apex::Application::Application()
{
    m_WindowInstance = std::make_unique<Apex::Window>(800, 600, "Apex Engine");
    m_CurrentScene = std::make_unique<DemoScene>();
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