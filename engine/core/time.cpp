#include "time.h"

#include <GLFW/glfw3.h>

/* static */ float Apex::Time::getTime() {return static_cast<float>(glfwGetTime());}

/* static */ void Apex::Time::update()
 {
    float time = static_cast<float>(glfwGetTime());
    ms_DeltaTime = time - ms_LastFrameTime;
    ms_LastFrameTime = time;
 }