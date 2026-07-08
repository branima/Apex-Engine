#pragma once

#include <glad/glad.h>

#include <string>

namespace Apex
{
    class Shader
    {
    public:
        unsigned int m_ID;

        Shader(const char* vertexPath, const char* fragmentPath);
        ~Shader() = default;

        void use();

        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;

    private:
        void checkCompileErrors(GLuint shader, std::string type);
    };
}