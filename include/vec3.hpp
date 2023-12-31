#ifndef QUIKMAFF_VEC3_HPP
#define QUIKMAFF_VEC3_HPP

#include "concepts.hpp"
#include "functions.hpp"

template <IsNumberT T>
struct vec2;
template <IsNumberT T>
struct vec4;

template <IsNumberT T>
struct vec3 {

    // Data
    T x;
    T y;
    T z;

    // Default constructor
    constexpr vec3(T x_, T y_, T z_) : x{x_}, y{y_}, z{z_} {}

    // Single value constructor
    constexpr vec3(T value) : x{value}, y{value}, z{value} {}

    // Zero constructor
    constexpr vec3() : x{static_cast<T>(0.0)}, y{static_cast<T>(0.0)}, z{static_cast<T>(0.0)} {}

    // Conversion scalar constructors
    template <IsNumberT X, IsNumberT Y, IsNumberT Z>
    constexpr vec3(X _x, Y _y, Z _z)
        : x(static_cast<T>(_x)), y(static_cast<T>(_y)), z(static_cast<T>(_z))
    {
    }

    // Conversion vector constructors
    template <IsNumberT X, IsNumberT B>
    constexpr vec3(vec2<X> const &_xy, B _z)
        : x(static_cast<T>(_xy.x)), y(static_cast<T>(_xy.y)), z(static_cast<T>(_z))
    {
    }

    template <IsNumberT A, IsNumberT X>
    constexpr vec3(A _x, vec2<X> const &_yz)
        : x(static_cast<T>(_x)), y(static_cast<T>(_yz.x)), z(static_cast<T>(_yz.y))
    {
    }

    template <IsNumberT X>
    constexpr vec3(vec3<X> const &v)
        : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z))
    {
    }

    template <IsNumberT X>
    constexpr vec3(vec4<X> const &v)
        : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z))
    {
    }

    // Static factory methods
    static constexpr vec3 zero() { return vec3(static_cast<T>(0.0)); }
    static constexpr vec3 ones() { return vec3(static_cast<T>(1.0)); }

    static constexpr std::size_t componentCount() { return 3; }
    static constexpr std::size_t size() { return sizeof(vec3<T>); }

    // -- Component accesses --
    constexpr T &operator[](uint32_t i)
    {
        QM_ASSERT(i >= 0 && i < this->componentCount());
        switch (i) {
            default:
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
        }
    }

    constexpr T operator[](uint32_t i) const
    {
        QM_ASSERT(i >= 0 && i < this->componentCount());
        switch (i) {
            default:
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
        }
    }
    // Arithmetic Operators
    constexpr vec3 operator+(const vec3 &other) const
    {
        return vec3(x + other.x, y + other.y, z + other.z);
    }

    constexpr vec3 operator-(const vec3 &other) const
    {
        return vec3(x - other.x, y - other.y, z - other.z);
    }

    constexpr vec3 operator*(float scalar) const
    {
        return vec3(x * scalar, y * scalar, z * scalar);
    }

    constexpr vec3 operator/(float scalar) const
    {
        if (scalar != 0.0f) {
            return vec3(x / scalar, y / scalar, z / scalar);
        }
        else {
            throw std::invalid_argument("Division by zero");
        }
    }

    constexpr float length() const { return qm::sqrt(x * x + y * y + z * z); }

    constexpr float lengthSquared() const { return (x * x + y * y + z * z); }

    void normalize()
    {
        float len = length();
        if (len != 0.0f) {
            x /= len;
            y /= len;
            z /= len;
        }
    }

    constexpr vec3 normalized() const
    {
        vec3 result(*this); // Create a copy
        result.normalize();
        return result;
    }

    constexpr float dot(const vec3 &other) const { return x * other.x + y * other.y + z * other.z; }

    // Cross Product (Vector Product)
    vec3<float> cross(const vec3<T> &v) const
    {
        static_assert(IsFloatVec<T, 3>, "Input vector must be a float vector of size 3.");
        return vec3<float>((y * v.z) - (z * v.y), (z * v.x) - (x * v.z), (x * v.y) - (y * v.x));
    }

    // Unary arithmetic operators
    template <IsNumberT A>
    constexpr vec3 &operator=(vec3<A> const &v)
    {
        this->x = static_cast<T>(v.x);
        this->y = static_cast<T>(v.y);
        this->z = static_cast<T>(v.z);
        return *this;
    }

    template <IsNumberT A>
    constexpr vec3 &operator+=(A scalar)
    {
        this->x += static_cast<T>(scalar);
        this->y += static_cast<T>(scalar);
        this->z += static_cast<T>(scalar);
        return *this;
    }

    template <IsNumberT A>
    constexpr vec3 &operator+=(vec3<A> const &v)
    {
        this->x += static_cast<T>(v.x);
        this->y += static_cast<T>(v.y);
        this->z += static_cast<T>(v.z);
        return *this;
    }

    template <IsNumberT A>
    constexpr vec3 &operator-=(A scalar)
    {
        this->x -= static_cast<T>(scalar);
        this->y -= static_cast<T>(scalar);
        this->z -= static_cast<T>(scalar);
        return *this;
    }

    template <IsNumberT A>
    constexpr vec3 &operator-=(vec3<A> const &v)
    {
        this->x -= static_cast<T>(v.x);
        this->y -= static_cast<T>(v.y);
        this->z -= static_cast<T>(v.z);
        return *this;
    }

    template <IsNumberT A>
    constexpr vec3 &operator*=(A scalar)
    {
        this->x *= static_cast<T>(scalar);
        this->y *= static_cast<T>(scalar);
        this->z *= static_cast<T>(scalar);
        return *this;
    }

    template <IsNumberT A>
    constexpr vec3 &operator*=(vec3<A> const &v)
    {
        this->x *= static_cast<T>(v.x);
        this->y *= static_cast<T>(v.y);
        this->z *= static_cast<T>(v.z);
        return *this;
    }

    template <IsNumberT A>
    constexpr vec3 &operator/=(A scalar)
    {
        this->x /= static_cast<T>(scalar);
        this->y /= static_cast<T>(scalar);
        this->z /= static_cast<T>(scalar);
        return *this;
    }

    template <IsNumberT A>
    constexpr vec3 &operator/=(vec3<A> const &v)
    {
        this->x /= static_cast<T>(v.x);
        this->y /= static_cast<T>(v.y);
        this->z /= static_cast<T>(v.z);
        return *this;
    }

    // Increment and decrement operators

    constexpr vec3 &operator++()
    {
        ++this->x;
        ++this->y;
        ++this->z;
        return *this;
    }

    constexpr vec3 &operator--()
    {
        --this->x;
        --this->y;
        --this->z;
        return *this;
    }

    constexpr vec3 operator++(int)
    {
        vec3 result(*this);
        ++*this;
        return result;
    }

    constexpr vec3 operator--(int)
    {
        vec3 result(*this);
        --*this;
        return result;
    }

    // Compound assignment operators

    // Modulus operator
    constexpr vec3 &operator%=(const vec3 &v)
    {
        x %= v.x;
        y %= v.y;
        z %= v.z;
        return *this;
    }

    constexpr vec3 &operator%=(T scalar)
    {
        x %= scalar;
        y %= scalar;
        z %= scalar;
        return *this;
    }

    // Bitwise AND operator
    template <IsIntegerT A>
    constexpr vec3 &operator&=(const vec3<A> &v)
    {
        x &= v.x;
        y &= v.y;
        z &= v.z;
        return *this;
    }

    template <IsIntegerT A>
    constexpr vec3 &operator&=(A scalar)
    {
        x &= scalar;
        y &= scalar;
        z &= scalar;
        return *this;
    }

    // Bitwise OR operator
    template <IsIntegerT A>
    constexpr vec3 &operator|=(const vec3<A> &v)
    {
        x |= v.x;
        y |= v.y;
        z |= v.z;
        return *this;
    }

    template <IsIntegerT A>
    constexpr vec3 &operator|=(A scalar)
    {
        x |= scalar;
        y |= scalar;
        z |= scalar;
        return *this;
    }

    // Bitwise XOR operator
    template <IsIntegerT A>
    constexpr vec3 &operator^=(const vec3<A> &v)
    {
        x ^= v.x;
        y ^= v.y;
        z ^= v.z;
        return *this;
    }

    template <IsIntegerT A>
    constexpr vec3 &operator^=(A scalar)
    {
        x ^= scalar;
        y ^= scalar;
        z ^= scalar;
        return *this;
    }

    // Bitwise left shift operator
    template <IsIntegerT A>
    constexpr vec3 &operator<<=(const vec3<A> &v)
    {
        x <<= v.x;
        y <<= v.y;
        z <<= v.z;
        return *this;
    }

    template <IsIntegerT A>
    constexpr vec3 &operator<<=(A numBits)
    {
        x <<= numBits;
        y <<= numBits;
        z <<= numBits;
        return *this;
    }

    // Bitwise right shift operator
    template <IsIntegerT A>
    constexpr vec3 &operator>>=(const vec2<A> &v)
    {
        x >>= v.x;
        y >>= v.y;
        z >>= v.z;
        return *this;
    }

    template <IsIntegerT A>
    constexpr vec3 &operator>>=(A numBits)
    {
        x >>= numBits;
        y >>= numBits;
        z >>= numBits;
        return *this;
    }

    // Comparison Operators
    template <IsNumberT A>
    constexpr bool operator==(const vec3<A> &v)
    {
        return this->x == v.x && this->y == v.y && this->z == v.z;
    }

    template <IsNumberT A>
    constexpr bool operator!=(const vec3<A> &v)
    {
        return !(this == v);
    }

    template <IsNumberT A>
    constexpr bool operator<(const vec3<A> &v)
    {
        if (this->x != v.x)
            return this->x < v.x;
        if (this->y != v.y)
            return this->y < v.y;
        return this->z < v.z;
    }

    template <IsNumberT A>
    constexpr bool operator<=(const vec3<A> &v)
    {
        return !(this < v);
    }

    template <IsNumberT A>
    constexpr bool operator>(const vec3<A> &v)
    {
        return this < v;
    }

    template <IsNumberT A>
    constexpr bool operator>=(const vec3<A> &v)
    {
        return !(this < v);
    }

    // String / Print functions
    constexpr std::string toString() const
    {
        if constexpr (IsFloatingPointT<decltype(x)>) {
            return std::format("vec3(x: {:.5f}, y: {:.5f}, z: {:.5f})", static_cast<double>(x),
                               static_cast<double>(y), static_cast<double>(z));
        }
        else {
            return std::format("vec3(x: {}, y: {}, z: {})", x, y, z);
        }
    }

    void print() const { std::cout << toString() << '\n'; }
};

// Friend fuctions
template <IsNumberT T>
constexpr vec3<T> operator+(const vec3<T> &lhs, const vec3<T> &rhs)
{
    return vec3<T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

template <IsNumberT T>
constexpr vec3<T> operator-(const vec3<T> &lhs, const vec3<T> &rhs)
{
    return vec3<T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

template <IsNumberT T>
constexpr vec3<T> operator/(const vec3<T> &vec, float scalar)
{
    if (scalar != 0.0f) {
        return vec3<T>(vec.x / scalar, vec.y / scalar, vec.z / scalar);
    }
    else {
        throw std::invalid_argument("Division by zero");
    }
}

template <IsNumberT T>
constexpr vec3<T> operator*(const vec3<T> &vec, float scalar)
{
    return vec3<T>(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

// Support commutative multiplication
template <IsNumberT T>
constexpr vec3<T> operator*(float scalar, const vec3<T> &vec)
{
    return vec3<T>(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

// Comparison Operators
template <IsNumberT T>
constexpr bool operator==(const vec3<T> &lhs, const vec3<T> &rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

template <IsNumberT T>
constexpr bool operator!=(const vec3<T> &lhs, const vec3<T> &rhs)
{
    return !(lhs == rhs);
}

template <IsNumberT T>
constexpr bool operator<(const vec3<T> &lhs, const vec3<T> &rhs)
{
    if (lhs.x != rhs.x)
        return lhs.x < rhs.x;
    if (lhs.y != rhs.y)
        return lhs.y < rhs.y;
    return lhs.z < rhs.z;
}

template <IsNumberT T>
constexpr bool operator<=(const vec3<T> &lhs, const vec3<T> &rhs)
{
    return !(rhs < lhs);
}

template <IsNumberT T>
constexpr bool operator>(const vec3<T> &lhs, const vec3<T> &rhs)
{
    return rhs < lhs;
}

template <IsNumberT T>
constexpr bool operator>=(const vec3<T> &lhs, const vec3<T> &rhs)
{
    return !(lhs < rhs);
}

// Swizzle Operators
template <IsNumberT T>
constexpr vec3<T> zyx(const vec3<T> &v)
{
    return vec3<T>(v.z, v.y, v.x);
}

template <IsNumberT T>
constexpr vec3<T> wxy(const vec3<T> &v)
{
    return vec3<T>(v.w, v.x, v.y);
}

template <IsNumberT T>
constexpr vec3<T> xxx(const vec3<T> &v)
{
    return vec3<T>(v.x, v.x, v.x);
}

template <IsNumberT T>
constexpr vec3<T> yyy(const vec3<T> &v)
{
    return vec3<T>(v.y, v.y, v.y);
}

template <IsNumberT T>
constexpr vec3<T> zzz(const vec3<T> &v)
{
    return vec3<T>(v.z, v.z, v.z);
}

using vec3f = vec3<float>;
using vec3i = vec3<int>;
using vec3u = vec3<unsigned int>;

#endif // QUIKMAFF_VEC3_HPP