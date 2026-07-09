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
    engine/core/application.cpp
    engine/core/elementbuffer.cpp
    engine/core/input.cpp
    engine/core/renderer.cpp
    engine/core/shader.cpp
    engine/core/texture.cpp
    engine/core/time.cpp
    engine/core/vertexbuffer.cpp
    engine/core/vertexarray.cpp
    engine/core/window.cpp
    external/glad/src/glad.c
    game/asteroidsScene.cpp
    game/demoscene.cpp
    src/main.cpp
    src/stb_image.cpp
)

target_include_directories(ApexEngine PRIVATE
    includes
    engine/core
    external/glad/include
    external/glm
    game
)

target_link_libraries(ApexEngine PRIVATE
    glfw
    opengl32
)