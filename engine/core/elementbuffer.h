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
            unsigned int getDataSize() const {return m_DataSize;}
            unsigned int getDataCount() const {return m_DataSize / sizeof(unsigned int);}

            void bind();
            void setData(const unsigned int* data, unsigned int dataSize, bool isDataDynamic = false);

        private:
            unsigned int m_ID{0};
            unsigned int m_DataSize{0};
    };
}