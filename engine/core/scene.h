#pragma once

#include "math.h"

namespace Apex
{
    class Scene
    {
        public:
            virtual ~Scene() = default;

            virtual void onRender() = 0;

            virtual float getWidth() const = 0;
            virtual float getHeight() const = 0;
            virtual Math::Vec2 getSceneCenter() const = 0;
    };
}