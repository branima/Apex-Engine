#include "application.h"

#include "demoscene.h"

Apex::Application::Application()
{
    m_WindowInstance = std::make_unique<Apex::Window>(800, 600, "Apex Engine");
    m_CurrentScene = std::make_unique<DemoScene>();
}

void processInput(Apex::Window& window)
{
    if (window.isKeyPressed(GLFW_KEY_ESCAPE))
    {
        window.setShouldWindowClose(true);
    }
}

void Apex::Application::run()
{
    while (!m_WindowInstance->getShouldWindowClose())
    {
        // Input: escape closes window
        processInput(*m_WindowInstance);

        m_CurrentScene->OnRender();

        m_WindowInstance->SwapBuffers();
        m_WindowInstance->PollEvents();
    }
}