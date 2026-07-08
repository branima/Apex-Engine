#pragma once

namespace Apex
{
    class Texture
    {
        public:
            Texture() = default;
            Texture(const char* path, bool shouldFlipVerticallyOnLoad = false);
            ~Texture();

            Texture(const Texture&) = delete;
            Texture& operator=(const Texture&) = delete;

            Texture(Texture&& other) noexcept;
            Texture& operator=(Texture&& other) noexcept;

            unsigned int getID() const {return m_ID;}

            void bindToTextureUnit(unsigned int unit);

        private:
            unsigned int m_ID{0};
    };
}