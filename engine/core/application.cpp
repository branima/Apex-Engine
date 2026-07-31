#include "application.h"

#include "imguilayer.h"
#include "input.h"
#include "renderer.h"

#include "asteroidsScene.h"

//#include "demoscene.h"

Apex::Application::Application()
{
    m_WindowInstance = std::make_unique<Apex::Window>(AsteroidsScene::SCENE_WIDTH, AsteroidsScene::SCENE_HEIGHT, "Apex Engine");

    ImGuiLayer::initialize(*m_WindowInstance);

    //m_CurrentScene = std::make_unique<DemoScene>();
    m_CurrentScene = std::make_unique<AsteroidsScene>();

    Renderer::initialize();
}

Apex::Application::~Application()
{
    ImGuiLayer::shutdown();
}

void Apex::Application::run()
{
    while (!m_WindowInstance->getShouldWindowClose())
    {
        Time::update();
        m_WindowInstance->pollEvents();

        m_CurrentScene->handleInputs(*m_WindowInstance);
        m_CurrentScene->update();

        ImGuiLayer::beginFrame();
        m_CurrentScene->onRender();
        m_CurrentScene->onDebugUI();
        ImGuiLayer::endFrame();

        m_WindowInstance->swapBuffers();
        Input::endFrame();
    }
}