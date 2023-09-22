#include "vec4.hpp"

#include "vec2.hpp"
#include "vec3.hpp"

/*
constexpr Vec4::Vec4() : x{0.0f}, y{0.0f}, z{0.0f}, w{0.0f} {}
constexpr Vec4::Vec4(f32 value) : x{value}, y{value}, z{value}, w{value} {}
constexpr Vec4::Vec4(const f32 *values) : x{values[0]}, y{values[1]}, z{values[2]}, w{values[3]} {}
constexpr Vec4::Vec4(const Vec2 &vec2, f32 z, f32 w) : x(vec2.x), y(vec2.y), z(z), w(w) {}
constexpr Vec4::Vec4(const Vec3 &vec3, f32 w) : x(vec3.x), y(vec3.y), z(vec3.z), w(w) {}

Vec2 Vec4::swizzle(int index1, int index2) const
{
    switch (index1) {
        case 0:
            return {x, y};
        case 1:
            return {y, z};
        case 2:
            return {z, w};
        case 3:
            return {x, w};
        default:
            // Handle invalid swizzle indices
            throw std::invalid_argument("Invalid swizzle indices for Vec4");
    }
}

Vec3 Vec4::swizzle(int index1, int index2, int index3) const
{
    switch (index1) {
        case 0:
            return {x, y, z};
        case 1:
            return {y, z, w};
        case 2:
            return {z, w, x};
        case 3:
            return {w, x, y};
        default:
            // Handle invalid swizzle indices
            throw std::invalid_argument("Invalid swizzle indices for Vec4");
    }
}

Vec4 Vec4::swizzle(int index1, int index2, int index3, int index4) const
{
    return {x, y, z, w}; // Swizzle to the same vector (no change)
}

*/
