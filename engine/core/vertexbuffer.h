#pragma once

namespace Apex
{
    class VertexBuffer
    {
        public:
            VertexBuffer();
            ~VertexBuffer();

            VertexBuffer(const VertexBuffer&) = delete;
            VertexBuffer& operator=(const VertexBuffer&) = delete;

            VertexBuffer(VertexBuffer&& other) noexcept;
            VertexBuffer& operator=(VertexBuffer&& other) noexcept;

            unsigned int getID() const {return m_ID;}

            void bind();
            void unbind();
            void setData(const float* data, int dataSize, bool isDataDynamic = false);

        private:
            unsigned int m_ID{0};
    };
}