#ifndef QUIKMAFF_VEC3_HPP
#define QUIKMAFF_VEC3_HPP

#include "concepts.hpp"
#include "functions.hpp"
#include <string>

template <NumberType T>
struct vec2;
template <NumberType T>
struct vec4;

template <NumberType T>
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
    template <NumberType X, NumberType Y, NumberType Z>
    constexpr vec3(X _x, Y _y, Z _z)
        : x(static_cast<T>(_x)), y(static_cast<T>(_y)), z(static_cast<T>(_z))
    {
    }

    // Conversion vector constructors
    template <NumberType X, NumberType B>
    constexpr vec3(vec2<X> const &_xy, B _z)
        : x(static_cast<T>(_xy.x)), y(static_cast<T>(_xy.y)), z(static_cast<T>(_z))
    {
    }

    template <NumberType A, NumberType X>
    constexpr vec3(A _x, vec2<X> const &_yz)
        : x(static_cast<T>(_x)), y(static_cast<T>(_yz.x)), z(static_cast<T>(_yz.y))
    {
    }

    template <NumberType X>
    constexpr vec3(vec3<X> const &v)
        : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z))
    {
    }

    template <NumberType X>
    constexpr vec3(vec4<X> const &v)
        : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z))
    {
    }

    // Static factory methods
    static constexpr vec3 zero() { return vec3(static_cast<T>(0.0)); }
    static constexpr vec3 ones() { return vec3(static_cast<T>(1.0)); }

    static constexpr std::size_t length() { return 3; }
    static constexpr std::size_t size() { return sizeof(vec3<T>); }

    // -- Component accesses --
    constexpr T &operator[](uint32_t i)
    {
        QM_ASSERT(i >= 0 && i < this->length());
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
        QM_ASSERT(i >= 0 && i < this->length());
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

    // Unary arithmetic operators
    template <NumberType A>
    constexpr vec3 &operator=(vec3<A> const &v)
    {
        this->x = static_cast<T>(v.x);
        this->y = static_cast<T>(v.y);
        this->z = static_cast<T>(v.z);
        return *this;
    }

    template <NumberType A>
    constexpr vec3 &operator+=(A scalar)
    {
        this->x += static_cast<T>(scalar);
        this->y += static_cast<T>(scalar);
        this->z += static_cast<T>(scalar);
        return *this;
    }

    template <NumberType A>
    constexpr vec3 &operator+=(vec3<A> const &v)
    {
        this->x += static_cast<T>(v.x);
        this->y += static_cast<T>(v.y);
        this->z += static_cast<T>(v.z);
        return *this;
    }

    template <NumberType A>
    constexpr vec3 &operator-=(A scalar)
    {
        this->x -= static_cast<T>(scalar);
        this->y -= static_cast<T>(scalar);
        this->z -= static_cast<T>(scalar);
        return *this;
    }

    template <NumberType A>
    constexpr vec3 &operator-=(vec3<A> const &v)
    {
        this->x -= static_cast<T>(v.x);
        this->y -= static_cast<T>(v.y);
        this->z -= static_cast<T>(v.z);
        return *this;
    }

    template <NumberType A>
    constexpr vec3 &operator*=(A scalar)
    {
        this->x *= static_cast<T>(scalar);
        this->y *= static_cast<T>(scalar);
        this->z *= static_cast<T>(scalar);
        return *this;
    }

    template <NumberType A>
    constexpr vec3 &operator*=(vec3<A> const &v)
    {
        this->x *= static_cast<T>(v.x);
        this->y *= static_cast<T>(v.y);
        this->z *= static_cast<T>(v.z);
        return *this;
    }

    template <NumberType A>
    constexpr vec3 &operator/=(A scalar)
    {
        this->x /= static_cast<T>(scalar);
        this->y /= static_cast<T>(scalar);
        this->z /= static_cast<T>(scalar);
        return *this;
    }

    template <NumberType A>
    constexpr vec3 &operator/=(vec3<A> const &v)
    {
        this->x /= static_cast<T>(v.x);
        this->y /= static_cast<T>(v.y);
        this->z /= static_cast<T>(v.z);
        return *this;
    }

    // Increment and decrement operators

    vec3 &operator++()
    {
        ++this->x;
        ++this->y;
        ++this->z;
        return *this;
    }

    vec3 &operator--()
    {
        --this->x;
        --this->y;
        --this->z;
        return *this;
    }

    vec3 operator++(int)
    {
        vec3 result(*this);
        ++*this;
        return result;
    }

    vec3 operator--(int)
    {
        vec3 result(*this);
        --*this;
        return result;
    }

    // Compound assignment operators

    // Modulus operator
    vec3 &operator%=(const vec3 &v)
    {
        x %= v.x;
        y %= v.y;
        z %= v.z;
        return *this;
    }

    vec3 &operator%=(T scalar)
    {
        x %= scalar;
        y %= scalar;
        z %= scalar;
        return *this;
    }

    // Bitwise AND operator
    template <IntegerType A>
    vec3 &operator&=(const vec3<A> &v)
    {
        x &= v.x;
        y &= v.y;
        z &= v.z;
        return *this;
    }

    template <IntegerType A>
    vec3 &operator&=(A scalar)
    {
        x &= scalar;
        y &= scalar;
        z &= scalar;
        return *this;
    }

    // Bitwise OR operator
    template <IntegerType A>
    vec3 &operator|=(const vec3<A> &v)
    {
        x |= v.x;
        y |= v.y;
        z |= v.z;
        return *this;
    }

    template <IntegerType A>
    vec3 &operator|=(A scalar)
    {
        x |= scalar;
        y |= scalar;
        z |= scalar;
        return *this;
    }

    // Bitwise XOR operator
    template <IntegerType A>
    vec3 &operator^=(const vec3<A> &v)
    {
        x ^= v.x;
        y ^= v.y;
        z ^= v.z;
        return *this;
    }

    template <IntegerType A>
    vec3 &operator^=(A scalar)
    {
        x ^= scalar;
        y ^= scalar;
        z ^= scalar;
        return *this;
    }

    // Bitwise left shift operator
    template <IntegerType A>
    vec3 &operator<<=(const vec3<A> &v)
    {
        x <<= v.x;
        y <<= v.y;
        z <<= v.z;
        return *this;
    }

    template <IntegerType A>
    vec3 &operator<<=(A numBits)
    {
        x <<= numBits;
        y <<= numBits;
        z <<= numBits;
        return *this;
    }

    // Bitwise right shift operator
    template <IntegerType A>
    vec3 &operator>>=(const vec2<A> &v)
    {
        x >>= v.x;
        y >>= v.y;
        z >>= v.z;
        return *this;
    }

    template <IntegerType A>
    vec3 &operator>>=(A numBits)
    {
        x >>= numBits;
        y >>= numBits;
        z >>= numBits;
        return *this;
    }

    // String / Print functions
    constexpr std::string toString() const
    {
        if constexpr (FloatingPointType<decltype(x)>) {
            return std::format("vec3(x: {:.5f}, y: {:.5f}, z: {:.5f})", static_cast<double>(x),
                               static_cast<double>(y), static_cast<double>(z));
        }
        else {
            return std::format("vec3(x: {}, y: {}, z: {})", x, y, z);
        }
    }

    void print() const { std::cout << toString() << '\n'; }
};

using vec3f = vec3<float>;
using vec3i = vec3<int>;
using vec3u = vec3<unsigned int>;

#endif // QUIKMAFF_VEC3_HPP