#pragma once

#include "scene.h"

#include "ship.h"

class AsteroidsScene : public Apex::Scene
{
    public:
        AsteroidsScene();
        ~AsteroidsScene() = default;

        void handleInputs(Apex::Window& window) override;
        void update();
        void onRender() override;

        static constexpr float SCENE_WIDTH = 1200.0f;
        static constexpr float SCENE_HEIGHT = 800.0f;

        float getWidth() const override
        {
            return SCENE_WIDTH;
        }

        float getHeight() const override
        {
            return SCENE_HEIGHT;
        }

    private:
        Ship m_Ship;

        Apex::Math::Vec3 m_MovementDirection;
        Apex::Math::Vec2 m_CursorPosition;
};