#include "time.h"

#include <GLFW/glfw3.h>

/* static */ float Apex::Time::getTime() {return static_cast<float>(glfwGetTime());}