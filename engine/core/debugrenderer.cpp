#include "debugrenderer.h"

#include "renderer.h"

Apex::DebugRenderer::DebugRenderer()
    : m_LineShader("shaders/gizmoShader.vs", "shaders/gizmoShader.fs")
{
    std::vector<Apex::Math::Vec3> vertices;
    vertices.reserve(CIRCLE_VERTEX_COUNT);

    for (int i = 0; i < CIRCLE_VERTEX_COUNT; ++i)
    {
        const float angle = static_cast<float>(i) / static_cast<float>(CIRCLE_VERTEX_COUNT) * Apex::Math::TWO_PI;
        vertices.emplace_back(std::cos(angle), std::sin(angle), 0.0f);
    }

    // Vertex array setup
    m_CircleVertexArray.bind();

    // Vertex data buffer setup
    m_CircleVertexBuffer.bind();
    m_CircleVertexBuffer.setData(vertices.data(), CIRCLE_VERTEX_COUNT * sizeof(Math::Vec3));

    // Position attribute
    m_CircleVertexArray.setVertexAttribute(0, 3, sizeof(Math::Vec3), 0);

    // Unbind buffers and arrays after usage
    m_CircleVertexBuffer.unbind();
    m_CircleVertexArray.unbind();
}

void Apex::DebugRenderer::drawCircle(const Math::Vec3& center, float radius, const Math::Vec4& color)
{
    Math::Mat4 transform(1.0f);
    transform = Math::translate(transform, center);
    transform = Math::scale(transform, Math::Vec3(radius, radius, 1.0f));

    m_LineShader.use();
    m_LineShader.setMat4("transform", transform);
    m_LineShader.setMat4("projection", Renderer::getOrtographicProjMatrix());
    m_LineShader.setVec4("color", color);

    Renderer::drawLineLoop(m_CircleVertexArray, CIRCLE_VERTEX_COUNT);
}