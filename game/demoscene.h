#pragma once

#include "elementbuffer.h"
#include "renderer.h"
#include "scene.h"
#include "shader.h"
#include "texture.h"
#include "vertexarray.h"
#include "vertexbuffer.h"

class DemoScene : public Apex::Scene
{
    public:
        DemoScene();
        ~DemoScene() = default;

        void onRender() override;

        void shapeSetup();
        void shapeRender();

    private:

        Apex::VertexBuffer m_VtxBuffer;
        Apex::ElementBuffer m_ElBuffer;
        Apex::VertexArray m_VtxArray;

        Apex::Renderer m_Renderer;

        Apex::Texture m_Texture1, m_Texture2;
        Apex::Shader m_Shader;
};