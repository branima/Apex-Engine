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

            void bind() const;
            void unbind() const;
            void setData(const void* data, int dataSize, bool isDataDynamic = false);

        private:
            unsigned int m_ID{0};
    };
}