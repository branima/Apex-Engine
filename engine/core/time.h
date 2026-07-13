#pragma once

namespace Apex
{
    class Time
    {
        public:
            static void update();

            static float getTime();
            static float getDeltaTime() {return ms_DeltaTime;}

        private:
            inline static float ms_DeltaTime{0.0f};
            inline static float ms_LastFrameTime{0.0f};
    };
}