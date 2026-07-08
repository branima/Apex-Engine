#pragma once

namespace Apex
{
    class Scene
    {
        public:
            virtual ~Scene() = default;

            virtual void OnRender() = 0;
    };
}