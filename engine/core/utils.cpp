#include "utils.h"

namespace Apex
{
    std::mt19937 Utils::ms_RandomEngine(std::random_device{}());
}

int Apex::Utils::getRandomInt(int min, int max)
{
    return std::uniform_int_distribution<int>(min, max)(ms_RandomEngine);
}

float Apex::Utils::getRandomFloat(float min, float max)
{
    return std::uniform_real_distribution<float>(min, max)(ms_RandomEngine);
}