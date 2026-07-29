#include "spriterenderer.h"

#include "renderer.h"

Apex::SpriteRenderer::SpriteRenderer()
    : m_Shader("shaders/shader.vs", "shaders/shader.fs")
{
    const float vertices[] = {
        // positions // texture coords
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f // top left
    };

    const unsigned int indices[] = {
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
    m_VtxArray.setVertexAttribute(0, 3, 5 * sizeof(float), 0);

    // Texture attribute
    m_VtxArray.setVertexAttribute(1, 2, 5 * sizeof(float), 3 * sizeof(float));

    // Unbind buffers and arrays after usage
    m_VtxBuffer.unbind();
    m_VtxArray.unbind();

    // Shader config
    m_Shader.use();
    m_Shader.setInt("textureSample", 0);
}

void Apex::SpriteRenderer::render(const Transform& transform, const Texture& texture)
{
    texture.bindToTextureUnit(0);
    m_Shader.use();

    const Apex::Math::Mat4& transformMatrix = transform.getMatrix();
    m_Shader.setMat4("transform", transformMatrix);
    m_Shader.setMat4("projection", Apex::Renderer::getOrtographicProjMatrix());

    Apex::Renderer::drawElements(m_VtxArray, m_ElBuffer);
}

void Apex::SpriteRenderer::renderAcrossScene(float width, float height, const Texture& texture)
{
    texture.bindToTextureUnit(0);
    m_Shader.use();

    Apex::Math::Mat4 transMatrix = Apex::Math::getIdentity();
    transMatrix = Apex::Math::translate(transMatrix, Apex::Math::Vec3(width / 2.0f, height / 2.0f, 0.0f));
    transMatrix = Apex::Math::scale(transMatrix, Apex::Math::Vec3(width, height, 1.0f));
    m_Shader.setMat4("transform", transMatrix);
    m_Shader.setMat4("projection", Apex::Renderer::getOrtographicProjMatrix());

    Apex::Renderer::drawElements(m_VtxArray, m_ElBuffer);
}