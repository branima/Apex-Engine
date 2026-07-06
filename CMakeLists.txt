cmake_minimum_required(VERSION 3.20)

project(ApexEngine)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)

FetchContent_MakeAvailable(glfw)

add_executable(ApexEngine
    src/main.cpp
    src/stb_image.cpp
    external/glad/src/glad.c
)

target_include_directories(ApexEngine PRIVATE
    includes
    external/glad/include
    external/glm
)

target_link_libraries(ApexEngine PRIVATE
    glfw
    opengl32
)