#include "vec3.hpp"

#include "vec2.hpp"
#include "vec4.hpp"

/*
constexpr Vec3::Vec3(const Vec2 &vec2, float z) : x(vec2.x), y(vec2.y), z(z) {}
constexpr Vec3::Vec3(const Vec4 &vec4) : x(vec4.x), y(vec4.y), z(vec4.z) {}
constexpr Vec3::Vec3(int valueX, int valueY, int valueZ)
    : x{static_cast<f32>(valueX)}, y{static_cast<f32>(valueY)}, z{static_cast<f32>(valueZ)}
{
}
constexpr Vec3::Vec3(double valueX, double valueY, double valueZ)
    : x{static_cast<f32>(valueX)}, y{static_cast<f32>(valueY)}, z{static_cast<f32>(valueZ)}
{
}

Vec2 Vec3::swizzle(int index1, int index2) const
{
    switch (index1) {
        case 0:
            return {x, y};
        case 1:
            return {y, z};
        case 2:
            return {x, z};
        default:
            // Handle invalid swizzle indices
            throw std::invalid_argument("Invalid swizzle indices for Vec3");
    }
}

Vec3 Vec3::swizzle(int index1, int index2, int index3) const
{
    return {x, y, z}; // Swizzle to the same vector (no change)
}

*/
