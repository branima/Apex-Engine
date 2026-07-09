#pragma once

#include "renderer.h"
#include "scene.h"

class AsteroidsScene : public Apex::Scene
{
    public:
        AsteroidsScene() = default;
        ~AsteroidsScene() = default;

        void onRender() override;

    private:
        Apex::Renderer m_Renderer;
};