#pragma once

#include "math.h"
#include "window.h"

namespace Apex
{
    class Scene
    {
        public:
            virtual ~Scene() = default;

            virtual void handleInputs(Apex::Window& window) = 0;
            virtual void update() = 0;
            virtual void onRender() = 0;

            virtual float getWidth() const = 0;
            virtual float getHeight() const = 0;
            Math::Vec2 getSceneCenter() const {return {getWidth() * 0.5f, getHeight() * 0.5f};}

    };
}