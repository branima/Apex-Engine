#pragma once

#include <random>

namespace Apex
{
    class Utils
    {
        public:
            static int getRandomInt(int min, int max);
            static float getRandomFloat(float min, float max);

        private:
            static std::mt19937 ms_RandomEngine;
    };
}