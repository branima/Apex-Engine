#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <numbers>

namespace Apex::Math
{
    static constexpr float EPSILON = 0.0001f;
    inline constexpr float PI = std::numbers::pi_v<float>;
    inline constexpr float TWO_PI = PI * 2.0f;

    using Vec2 = glm::vec2;
    using Vec3 = glm::vec3;
    using Vec4 = glm::vec4;
    using Mat4 = glm::mat4;

    inline Mat4 getIdentity() {return Mat4(1.0f);}
    inline Vec3 getI() {return Vec3(1.0f, 0.0f, 0.0f);}
    inline Vec3 getJ() {return Vec3(0.0f, 1.0f, 0.0f);}
    inline Vec3 getK() {return Vec3(0.0f, 0.0f, 1.0f);}

    inline Mat4 translate(const Mat4& matrix, const Vec3& translation)
    {
        return glm::translate(matrix, translation);
    }

    inline Mat4 rotate(const Mat4& matrix, float radians, const Vec3& axis)
    {
        return glm::rotate(matrix, radians, axis);
    }

    inline Mat4 scale(const Mat4& matrix, const Vec3& scale)
    {
        return glm::scale(matrix, scale);
    }

    inline Vec3 normalize(const Vec3& vec)
    {
        return glm::length(vec) > Math::EPSILON ? glm::normalize(vec) : Vec3(0.0f);
    }

    inline float dotProduct(const Vec3& vecA, const Vec3& vecB)
    {
        return glm::dot(vecA, vecB);
    }

    inline float eulerToRadian(float eulerValue)
    {
        return glm::radians(eulerValue);
    }
}