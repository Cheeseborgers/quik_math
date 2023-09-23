#ifndef QUIKMAFF_VEC2_HPP
#define QUIKMAFF_VEC2_HPP

#include "concepts.hpp"
#include "functions.hpp"
#include <string>

template <IsNumberT T>
struct vec3;
template <IsNumberT T>
struct vec4;

template <IsNumberT T>
struct vec2 {

    // Data
    T x;
    T y;

    // Default constructor
    constexpr vec2(T x_, T y_) : x{x_}, y{y_} {}

    // Single value constructor
    constexpr vec2(T value) : x{value}, y{value} {}

    // Zero constructor
    constexpr vec2() : x{static_cast<T>(0)}, y{static_cast<T>(0)} {}

    // Conversion scalar constructors
    template <IsNumberT X, IsNumberT Y>
    constexpr vec2(X _x, Y _y) : x(static_cast<T>(_x)), y(static_cast<T>(_y))
    {
    }

    // Conversion vector constructors
    template <IsNumberT X>
    constexpr vec2(vec2<X> const &v) : x(static_cast<T>(v.x)), y(static_cast<T>(v.y))
    {
    }

    template <IsNumberT X>
    constexpr vec2(vec3<X> const &v) : x(static_cast<T>(v.x)), y(static_cast<T>(v.y))
    {
    }

    template <IsNumberT X>
    constexpr vec2(vec4<X> const &v) : x(static_cast<T>(v.x)), y(static_cast<T>(v.y))
    {
    }

    // Static factory methods
    static constexpr vec2 zero() { return vec2(static_cast<T>(0.0)); }
    static constexpr vec2 ones() { return vec2(static_cast<T>(1.0)); }

    //
    static constexpr std::size_t componentCount() { return 2; }
    static constexpr std::size_t size() { return sizeof(vec2<T>); }

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
        }
    }

    // Arithmetic Operators
    constexpr vec2 operator+(const vec2 &other) const { return vec2(x + other.x, y + other.y); }

    constexpr vec2 operator-(const vec2 &other) const { return vec2(x - other.x, y - other.y); }

    constexpr vec2 operator*(float scalar) const { return vec2(x * scalar, y * scalar); }

    constexpr vec2 operator/(float scalar) const
    {
        if (scalar != 0.0f) {
            return vec2(x / scalar, y / scalar);
        }
        else {
            throw std::invalid_argument("Division by zero");
        }
    }

    constexpr float length() const { return qm::sqrt(x * x + y * y); }

    constexpr float lengthSquared() const { return (x * x + y * y); }

    constexpr void normalize()
    {
        float len = length();
        if (len != 0.0f) {
            x /= len;
            y /= len;
        }
    }

    constexpr vec2 normalized() const
    {
        vec2 result(*this); // Create a copy
        result.normalize();
        return result;
    }

    constexpr float dot(const vec2 &other) const { return x * other.x + y * other.y; }

    // Unary arithmetic operators
    template <IsNumberT A>
    constexpr vec2 &operator=(vec2<A> const &v)
    {
        this->x = static_cast<T>(v.x);
        this->y = static_cast<T>(v.y);
        return *this;
    }

    template <IsNumberT A>
    constexpr vec2 &operator+=(A scalar)
    {
        this->x += static_cast<T>(scalar);
        this->y += static_cast<T>(scalar);
        return *this;
    }

    template <IsNumberT A>
    constexpr vec2 &operator+=(vec2<A> const &v)
    {
        this->x += static_cast<T>(v.x);
        this->y += static_cast<T>(v.y);
        return *this;
    }

    template <IsNumberT A>
    constexpr vec2 &operator-=(A scalar)
    {
        this->x -= static_cast<T>(scalar);
        this->y -= static_cast<T>(scalar);
        return *this;
    }

    template <IsNumberT A>
    constexpr vec2 &operator-=(vec2<A> const &v)
    {
        this->x -= static_cast<T>(v.x);
        this->y -= static_cast<T>(v.y);
        return *this;
    }

    template <IsNumberT A>
    constexpr vec2 &operator*=(A scalar)
    {
        this->x *= static_cast<T>(scalar);
        this->y *= static_cast<T>(scalar);
        return *this;
    }

    template <IsNumberT A>
    constexpr vec2 &operator*=(vec2<A> const &v)
    {
        this->x *= static_cast<T>(v.x);
        this->y *= static_cast<T>(v.y);
        return *this;
    }

    template <IsNumberT A>
    constexpr vec2 &operator/=(A scalar)
    {
        this->x /= static_cast<T>(scalar);
        this->y /= static_cast<T>(scalar);
        return *this;
    }

    template <IsNumberT A>
    constexpr vec2 &operator/=(vec2<A> const &v)
    {
        this->x /= static_cast<T>(v.x);
        this->y /= static_cast<T>(v.y);
        return *this;
    }

    // Increment and decrement operators
    constexpr vec2 &operator++()
    {
        ++this->x;
        ++this->y;
        return *this;
    }

    constexpr vec2 &operator--()
    {
        --this->x;
        --this->y;
        return *this;
    }

    constexpr vec2 operator++(int)
    {
        vec2 result(*this);
        ++*this;
        return result;
    }

    constexpr vec2 operator--(int)
    {
        vec2 result(*this);
        --*this;
        return result;
    }

    // Compound assignment operators

    // Modulus operator
    constexpr vec2 &operator%=(const vec2 &v)
    {
        x %= v.x;
        y %= v.y;
        return *this;
    }

    constexpr vec2 &operator%=(T scalar)
    {
        x %= scalar;
        y %= scalar;
        return *this;
    }

    // Bitwise AND operator
    template <IsIntegerT A>
    constexpr vec2 &operator&=(const vec2<A> &v)
    {
        x &= v.x;
        y &= v.y;
        return *this;
    }

    template <IsIntegerT A>
    constexpr vec2 &operator&=(A scalar)
    {
        x &= scalar;
        y &= scalar;
        return *this;
    }

    // Bitwise OR operator
    template <IsIntegerT A>
    constexpr vec2 &operator|=(const vec2<A> &v)
    {
        x |= v.x;
        y |= v.y;
        return *this;
    }

    template <IsIntegerT A>
    constexpr vec2 &operator|=(A scalar)
    {
        x |= scalar;
        y |= scalar;
        return *this;
    }

    // Bitwise XOR operator
    template <IsIntegerT A>
    constexpr vec2 &operator^=(const vec2<A> &v)
    {
        x ^= v.x;
        y ^= v.y;
        return *this;
    }

    template <IsIntegerT A>
    constexpr vec2 &operator^=(A scalar)
    {
        x ^= scalar;
        y ^= scalar;
        return *this;
    }

    // Bitwise left shift operator
    template <IsIntegerT A>
    constexpr vec2 &operator<<=(const vec2<A> &v)
    {
        x <<= v.x;
        y <<= v.y;
        return *this;
    }

    template <IsIntegerT A>
    constexpr vec2 &operator<<=(A numBits)
    {
        x <<= numBits;
        y <<= numBits;
        return *this;
    }

    // Bitwise right shift operator
    template <IsIntegerT A>
    constexpr vec2 &operator>>=(const vec2<A> &v)
    {
        x >>= v.x;
        y >>= v.y;
        return *this;
    }

    template <IsIntegerT A>
    constexpr vec2 &operator>>=(A numBits)
    {
        x >>= numBits;
        y >>= numBits;
        return *this;
    }

    // Comparison Operators
    template <IsNumberT A>
    constexpr bool operator==(const vec2<A> &v)
    {
        return this->x == v.x && this->y == v.y;
    }

    template <IsNumberT A>
    constexpr bool operator!=(const vec2<A> &v)
    {
        return !(this == v);
    }

    template <IsNumberT A>
    constexpr bool operator<(const vec2<A> &v)
    {
        if (this->x != v.x)
            return this->x < v.x;
        return this->y < v.y;
    }

    template <IsNumberT A>
    constexpr bool operator<=(const vec2<A> &v)
    {
        return !(this < v);
    }

    template <IsNumberT A>
    constexpr bool operator>(const vec2<A> &v)
    {
        return this < v;
    }

    template <IsNumberT A>
    constexpr bool operator>=(const vec2<A> &v)
    {
        return !(this < v);
    }

    // String / Print functions
    constexpr std::string toString() const
    {
        if constexpr (IsFloatingPointT<decltype(x)>) {
            return std::format("vec2(x: {:.5f}, y: {:.5f})", static_cast<double>(x),
                               static_cast<double>(y));
        }
        else {
            return std::format("vec2(x: {}, y: {})", x, y);
        }
    }

    void print() const { std::cout << toString() << '\n'; }
};

// Friend fuctions
template <IsNumberT T>
constexpr vec2<T> operator+(const vec2<T> &lhs, const vec2<T> &rhs)
{
    return vec2<T>(lhs.x + rhs.x, lhs.y + rhs.y);
}

template <IsNumberT T>
constexpr vec2<T> operator-(const vec2<T> &lhs, const vec2<T> &rhs)
{
    return vec2<T>(lhs.x - rhs.x, lhs.y - rhs.y);
}

template <IsNumberT T>
constexpr vec2<T> operator/(const vec2<T> &vec, float scalar)
{
    if (scalar != 0.0f) {
        return vec2<T>(vec.x / scalar, vec.y / scalar);
    }
    else {
        throw std::invalid_argument("Division by zero");
    }
}

template <IsNumberT T>
constexpr vec2<T> operator*(const vec2<T> &vec, float scalar)
{
    return vec2<T>(vec.x * scalar, vec.y * scalar);
}

// Support commutative multiplication
template <IsNumberT T>
constexpr vec2<T> operator*(float scalar, const vec2<T> &vec)
{
    return vec2<T>(vec.x * scalar, vec.y * scalar);
}

// Comparison Operators
template <IsNumberT T>
constexpr bool operator==(const vec2<T> &lhs, const vec2<T> &rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

template <IsNumberT T>
constexpr bool operator!=(const vec2<T> &lhs, const vec2<T> &rhs)
{
    return !(lhs == rhs);
}

template <IsNumberT T>
constexpr bool operator<(const vec2<T> &lhs, const vec2<T> &rhs)
{
    if (lhs.x != rhs.x)
        return lhs.x < rhs.x;
    return lhs.y < rhs.y;
}

template <IsNumberT T>
constexpr bool operator<=(const vec2<T> &lhs, const vec2<T> &rhs)
{
    return !(rhs < lhs);
}

template <IsNumberT T>
constexpr bool operator>(const vec2<T> &lhs, const vec2<T> &rhs)
{
    return rhs < lhs;
}

template <IsNumberT T>
constexpr bool operator>=(const vec2<T> &lhs, const vec2<T> &rhs)
{
    return !(lhs < rhs);
}

// Swizzle Operators
template <IsNumberT T>
constexpr vec2<T> xx(const vec2<T> &v)
{
    return vec2<T>(v.x, v.x);
}

template <IsNumberT T>
constexpr vec2<T> yy(const vec2<T> &v)
{
    return vec2<T>(v.y, v.y);
}

template <IsNumberT T>
constexpr vec2<T> yx(const vec2<T> &v)
{
    return vec2<T>(v.y, v.x);
}

using vec2f = vec2<float>;
using vec2i = vec2<int>;
using vec2u = vec2<unsigned int>;

#endif // QUIKMAFF_VEC2_HPP
