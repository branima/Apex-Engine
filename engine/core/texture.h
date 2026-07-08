#pragma once

namespace Apex
{
    class Texture
    {
        public:
            Texture(const char* path, bool shouldFlipVerticallyOnLoad = false);
            ~Texture();

            unsigned int getID() const {return m_ID;}

            void bindToTextureUnit(unsigned int unit);

        private:
            unsigned int m_ID{0};
    };
}