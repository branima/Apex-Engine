#include "ship.h"

#include "renderer.h"

Ship::Ship()
    : m_Texture("resources/textures/ship.png"),
      m_Shader(Apex::Shader("shaders/shader.vs", "shaders/shader.fs")),
      m_Transform(Apex::Math::Vec3(500.0f, 500.0f, 1.0f), Apex::Math::Vec3(200.0f, 200.0f, 1.0f))
{

    float vertices[] = {
        // positions // texture coords
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f // top left
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

Ship::Ship(const Apex::Math::Vec3& position, const Apex::Math::Vec3& scale)
    : Ship()
{
    m_Transform.setPosition(position);
    m_Transform.setScale(scale);
}

void Ship::onRender()
{
    m_Texture.bindToTextureUnit(0);
    m_Shader.use();

    Apex::Math::Mat4 trans = Apex::Math::getIdentity();
    trans = Apex::Math::translate(trans, m_Transform.getPosition());
    trans = Apex::Math::scale(trans, m_Transform.getScale());

    m_Shader.setMat4("transform", trans);
    m_Shader.setMat4("projection", Apex::Renderer::getOrtographicProjMatrix());

    Apex::Renderer::drawElements(m_VtxArray, m_ElBuffer);
}