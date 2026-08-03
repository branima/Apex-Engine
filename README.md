# Apex Engine

Apex Engine is a personal 2D game engine written in modern C++ using OpenGL. The project was created as a learning experience and as a portfolio piece to demonstrate engine architecture, rendering, gameplay programming, and clean C++ design.

## Features

* Modern OpenGL renderer
* Custom shader abstraction
* Texture loading and sprite rendering
* Input handling
* Time management (delta time)
* Circle collision detection
* Debug collision gizmos
* Asteroids demo game
* Modular engine architecture

## Technologies

* C++20
* OpenGL 3.3
* GLFW
* GLAD
* GLM
* stb_image
* CMake

## Current Project Status

The engine currently powers a complete Asteroids-style demo game featuring player movement, shooting, asteroid spawning and splitting, collision detection, lives, score, and game over flow.

The next major milestone is migrating the project to a custom Entity Component System (ECS) architecture to further improve scalability, data-oriented design, and engine flexibility.

## Goals

The purpose of Apex Engine is to explore game engine architecture from scratch while following clean programming principles and modern C++ practices. The project serves both as a learning platform and as a portfolio demonstrating intermediate engine and gameplay programming skills.

#Asteroids Demo

A small demo game based on the 1979 Atari classic, which serves to demonstrate engine's possibilities. Game is played as a small ship that can shoot the asteroids down in order to survive. Player has 3 lives and loses one when colliding with an asteroid. Shooting an asteroid means either destroying it completely or spliting it into several smaller ones, depending on its size. As passes by, asteroid spawn rate increases and they are moving at a higher speed.

## Controls
* W, A, S, D - Movement
* Mouse movement - Ship is always rotated towards the cursor
* Mouse left click - Shoot projectiles
* C - Enable collider gizmos
* TAB - Imgui with score, high score, FPS and several other debug details
