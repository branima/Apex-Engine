#pragma once

namespace Apex
{
    class ElementBuffer
    {
        public:
            ElementBuffer();
            ~ElementBuffer();

            ElementBuffer(const ElementBuffer&) = delete;
            ElementBuffer& operator=(const ElementBuffer&) = delete;

            ElementBuffer(ElementBuffer&& other) noexcept;
            ElementBuffer& operator=(ElementBuffer&& other) noexcept;

            unsigned int getID() const {return m_ID;}

            void bind();
            void setData(const unsigned int* data, int dataSize, bool isDataDynamic = false);

        private:
            unsigned int m_ID{0};
    };
}