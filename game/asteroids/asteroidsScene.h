#pragma once

#include "scene.h"

#include "ship.h"

class AsteroidsScene : public Apex::Scene
{
    public:
        AsteroidsScene();
        ~AsteroidsScene() = default;

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

        Apex::Math::Vec2 getSceneCenter() const override
        {
            return {
                SCENE_WIDTH * 0.5f,
                SCENE_HEIGHT * 0.5f
            };
        }

    private:
        Ship m_Ship;
};