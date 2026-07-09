#include "demoscene.h"

#include "math.h"
#include "time.h"

DemoScene::DemoScene()
{
    m_Texture1 = Apex::Texture("resources/textures/container.jpg");
    m_Texture2 = Apex::Texture("resources/textures/awesomeface.png", true);
    m_Shader = Apex::Shader("shaders/shader.vs", "shaders/shader.fs");

    //Prepare shaders and vertex information before render loop
    shapeSetup();
}

void DemoScene::shapeSetup()
{
    float vertices[] = {
        // positions // colors // texture coords
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    // Vertex array setup
    m_VtxArray.bind();

    // Vertex data buffer setup
    m_VtxBuffer.bind();
    m_VtxBuffer.setData(vertices, sizeof(vertices));

    // Element buffer setup
    m_ElBuffer.bind();
    m_ElBuffer.setData(indices, sizeof(indices));

    // Position attribute
    m_VtxArray.setVertexAttribute(0, 3, 8 * sizeof(float), 0);

    // Color attribute
    m_VtxArray.setVertexAttribute(1, 3, 8 * sizeof(float), 3 * sizeof(float));

    // Texture attribute
    m_VtxArray.setVertexAttribute(2, 2, 8 * sizeof(float), 6 * sizeof(float));

    // Unbind buffers and arrays after usage
    m_VtxBuffer.unbind();
    m_VtxArray.unbind();

    // Shader config
    m_Shader.use();
    m_Shader.setInt("texture1", 0);
    m_Shader.setInt("texture2", 1);
}

void DemoScene::shapeRender()
{
    m_Renderer.clearWindowWithColor(Apex::Math::Vec4(0.1f, 0.2f, 0.3f, 1.0f));

    m_Texture1.bindToTextureUnit(0);
    m_Texture2.bindToTextureUnit(1);

    m_Shader.use();

    m_Renderer.drawElements(m_VtxArray, m_ElBuffer);
}

void DemoScene::onRender()
{
    Apex::Math::Mat4 trans = Apex::Math::getIdentity();
    trans = Apex::Math::translate(trans, Apex::Math::Vec3(0.5f, -0.5f, 0.0f));
    trans = Apex::Math::rotate(trans, Apex::Time::getTime(), Apex::Math::getK());

    m_Shader.setMat4("transform", trans);

    shapeRender();
}