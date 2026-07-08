#pragma once

#include "scene.h"
#include "shader.h"
#include "texture.h"

class DemoScene : public Apex::Scene
{
    public:
        DemoScene();
        ~DemoScene();

        void OnRender() override;

    private:
        unsigned int m_VBO, m_VAO, m_EBO;
        Apex::Texture m_Texture1, m_Texture2;
        Apex::Shader m_Shader;
};