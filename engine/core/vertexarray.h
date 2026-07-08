#pragma once

namespace Apex
{
    class VertexArray
    {
        public:
            VertexArray();
            ~VertexArray();

            VertexArray(const VertexArray&) = delete;
            VertexArray& operator=(const VertexArray&) = delete;

            VertexArray(VertexArray&& other) noexcept;
            VertexArray& operator=(VertexArray&& other) noexcept;

            unsigned int getID() const {return m_ID;}

            void bind();
            void unbind();

            void setVertexAttribute(unsigned int location, unsigned int size, unsigned int stride, unsigned long long offset);

        private:
            unsigned int m_ID{0};
    };
}