#ifndef QUIKMAFF_VEC4_HPP
#define QUIKMAFF_VEC4_HPP

#include "concepts.hpp"
#include "functions.hpp"

template <IsNumberT T>
struct vec2;
template <IsNumberT T>
struct vec3;

template <IsNumberT T>
struct vec4 {

    // Data
    T x;
    T y;
    T z;
    T w;

    // Default constructor
    constexpr vec4(T x_, T y_, T z_, T w_) : x{x_}, y{y_}, z{z_}, w{w_} {}

    // Single value constructor
    constexpr vec4(T value) : x{value}, y{value}, z{value}, w{value} {}

    // Zero constructor
    constexpr vec4()
        : x{static_cast<T>(0.0)},
          y{static_cast<T>(0.0)},
          z{static_cast<T>(0.0)},
          w{static_cast<T>(0.0)}
    {
    }

    // Conversion scalar constructors
    template <IsNumberT X, IsNumberT Y, IsNumberT Z, IsNumberT W>
    constexpr vec4(X _x, Y _y, Z _z, W _w)
        : x(static_cast<T>(_x)), y(static_cast<T>(_y)), z(static_cast<T>(_z)), w(static_cast<T>(_w))
    {
    }

    // Conversion vector constructors
    template <IsNumberT X, IsNumberT A, IsNumberT B>
    constexpr vec4(vec2<X> const &_xy, A _z, B _w)
        : x(static_cast<T>(_xy.x)),
          y(static_cast<T>(_xy.y)),
          z(static_cast<T>(_z)),
          w(static_cast<T>(_w))
    {
    }

    template <IsNumberT A, IsNumberT X, IsNumberT B>
    constexpr vec4(A _x, vec2<X> const &_yz, B _w)
        : x(static_cast<T>(_x)),
          y(static_cast<T>(_yz.x)),
          z(static_cast<T>(_yz.y)),
          w(static_cast<T>(_w))
    {
    }

    template <IsNumberT A, IsNumberT B, IsNumberT X>
    constexpr vec4(A _x, B _y, vec2<X> const &_zw)
        : x(static_cast<T>(_x)),
          y(static_cast<T>(_y)),
          z(static_cast<T>(_zw.x)),
          w(static_cast<T>(_zw.y))
    {
    }

    template <IsNumberT X, IsNumberT A>
    constexpr vec4(vec3<X> const &_xyz, A _w)
        : x(static_cast<T>(_xyz.x)),
          y(static_cast<T>(_xyz.y)),
          z(static_cast<T>(_xyz.z)),
          w(static_cast<T>(_w))
    {
    }

    template <IsNumberT A, IsNumberT X>
    constexpr vec4(A _x, vec3<X> const &_yzw)
        : x(static_cast<T>(_x)),
          y(static_cast<T>(_yzw.x)),
          z(static_cast<T>(_yzw.y)),
          w(static_cast<T>(_yzw.z))
    {
    }

    template <IsNumberT A, IsNumberT B>
    constexpr vec4(vec2<A> const &_xy, vec2<B> const &_zw)
        : x(static_cast<T>(_xy.x)),
          y(static_cast<T>(_xy.y)),
          z(static_cast<T>(_zw.x)),
          w(static_cast<T>(_zw.y))
    {
    }
    template <IsNumberT X>
    constexpr vec4(vec4<X> const &v)
        : x(static_cast<T>(v.x)),
          y(static_cast<T>(v.y)),
          z(static_cast<T>(v.z)),
          w(static_cast<T>(v.w))
    {
    }

    // Static factory methods
    static constexpr vec4 zero() { return vec4(static_cast<T>(0.0)); }
    static constexpr vec4 ones() { return vec4(static_cast<T>(1.0)); }

    static constexpr std::size_t componentCount() { return 4; }
    static constexpr std::size_t size() { return sizeof(vec4<T>); }

    // Component accesses
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
            case 3:
                return w;
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
            case 3:
                return w;
        }
    }

    // Arithmetic Operators
    constexpr vec4 operator+(const vec4 &other) const
    {
        return vec4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    constexpr vec4 operator-(const vec4 &other) const
    {
        return vec4(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    constexpr vec4 operator*(float scalar) const
    {
        return vec4(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    constexpr vec4 operator/(float scalar) const
    {
        if (scalar != 0.0f) {
            return vec4(x / scalar, y / scalar, z / scalar, w / scalar);
        }
        else {
            throw std::invalid_argument("Division by zero");
        }
    }

    constexpr float length() const { return qm::sqrt(x * x + y * y + z * z + w * w); }

    constexpr float lengthSquared() const { return (x * x + y * y + z * z + w * w); }

    constexpr void normalize()
    {
        float len = length();
        if (len != 0.0f) {
            x /= len;
            y /= len;
            z /= len;
            w /= len;
        }
    }

    constexpr vec4 normalized() const
    {
        vec4 result(*this); // Create a copy
        result.normalize();
        return result;
    }

    template <IsNumberT A>
    constexpr float dot(const vec4<A> &other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    // Hadamard Product (Component-wise Multiplication)
    template <IsNumberT A>
    constexpr vec4<T> hadamard(const vec4<A> &v) const
    {
        return vec4<T>(x * v.x, y * v.y, z * v.z, w * v.w);
    }

    // Unary arithmetic operators
    template <IsNumberT A>
    constexpr vec4 &operator=(vec4<A> const &v)
    {
        this->x = static_cast<T>(v.x);
        this->y = static_cast<T>(v.y);
        this->z = static_cast<T>(v.z);
        this->w = static_cast<T>(v.w);
        return *this;
    }

    template <IsNumberT A>
    constexpr vec4 &operator+=(A scalar)
    {
        this->x += static_cast<T>(scalar);
        this->y += static_cast<T>(scalar);
        this->z += static_cast<T>(scalar);
        this->w += static_cast<T>(scalar);
        return *this;
    }

    template <IsNumberT A>
    constexpr vec4 &operator+=(vec4<A> const &v)
    {
        this->x += static_cast<T>(v.x);
        this->y += static_cast<T>(v.y);
        this->z += static_cast<T>(v.z);
        this->w += static_cast<T>(v.w);
        return *this;
    }

    template <IsNumberT A>
    constexpr vec4 &operator-=(A scalar)
    {
        this->x -= static_cast<T>(scalar);
        this->y -= static_cast<T>(scalar);
        this->z -= static_cast<T>(scalar);
        this->w -= static_cast<T>(scalar);
        return *this;
    }

    template <IsNumberT A>
    constexpr vec4 &operator-=(vec4<A> const &v)
    {
        this->x -= static_cast<T>(v.x);
        this->y -= static_cast<T>(v.y);
        this->z -= static_cast<T>(v.z);
        this->w -= static_cast<T>(v.w);
        return *this;
    }

    template <IsNumberT A>
    constexpr vec4 &operator*=(A scalar)
    {
        this->x *= static_cast<T>(scalar);
        this->y *= static_cast<T>(scalar);
        this->z *= static_cast<T>(scalar);
        this->w *= static_cast<T>(scalar);
        return *this;
    }

    template <IsNumberT A>
    constexpr vec4 &operator*=(vec4<A> const &v)
    {
        this->x *= static_cast<T>(v.x);
        this->y *= static_cast<T>(v.y);
        this->z *= static_cast<T>(v.z);
        this->w *= static_cast<T>(v.w);
        return *this;
    }

    template <IsNumberT A>
    constexpr vec4 &operator/=(A scalar)
    {
        this->x /= static_cast<T>(scalar);
        this->y /= static_cast<T>(scalar);
        this->z /= static_cast<T>(scalar);
        this->w /= static_cast<T>(scalar);
        return *this;
    }

    template <IsNumberT A>
    constexpr vec4 &operator/=(vec4<A> const &v)
    {
        this->x /= static_cast<T>(v.x);
        this->y /= static_cast<T>(v.y);
        this->z /= static_cast<T>(v.z);
        this->w /= static_cast<T>(v.w);
        return *this;
    }

    // Increment and decrement operators

    constexpr vec4 &operator++()
    {
        ++this->x;
        ++this->y;
        ++this->z;
        ++this->w;
        return *this;
    }

    constexpr vec4 &operator--()
    {
        --this->x;
        --this->y;
        --this->z;
        --this->w;
        return *this;
    }

    constexpr vec4 operator++(int)
    {
        vec4 result(*this);
        ++*this;
        return result;
    }

    constexpr vec4 operator--(int)
    {
        vec4 result(*this);
        --*this;
        return result;
    }

    // Compound assignment operators

    // Modulus operator
    constexpr vec4 &operator%=(const vec4 &v)
    {
        x %= v.x;
        y %= v.y;
        z %= v.z;
        w %= v.w;
        return *this;
    }

    constexpr vec4 &operator%=(T scalar)
    {
        x %= scalar;
        y %= scalar;
        z %= scalar;
        w %= scalar;
        return *this;
    }

    // Bitwise AND operator
    template <IsIntegerT A>
    constexpr vec4 &operator&=(const vec4<A> &v)
    {
        x &= v.x;
        y &= v.y;
        z &= v.z;
        w &= v.w;
        return *this;
    }

    template <IsIntegerT A>
    constexpr vec4 &operator&=(A scalar)
    {
        x &= scalar;
        y &= scalar;
        z &= scalar;
        w &= scalar;
        return *this;
    }

    // Bitwise OR operator
    template <IsIntegerT A>
    constexpr vec4 &operator|=(const vec4<A> &v)
    {
        x |= v.x;
        y |= v.y;
        z |= v.z;
        w |= v.w;
        return *this;
    }

    template <IsIntegerT A>
    constexpr vec4 &operator|=(A scalar)
    {
        x |= scalar;
        y |= scalar;
        z |= scalar;
        w |= scalar;
        return *this;
    }

    // Bitwise XOR operator
    template <IsIntegerT A>
    constexpr vec4 &operator^=(const vec4<A> &v)
    {
        x ^= v.x;
        y ^= v.y;
        z ^= v.z;
        w ^= v.w;
        return *this;
    }

    template <IsIntegerT A>
    constexpr vec4 &operator^=(A scalar)
    {
        x ^= scalar;
        y ^= scalar;
        z ^= scalar;
        w ^= scalar;
        return *this;
    }

    // Bitwise left shift operator
    template <IsIntegerT A>
    constexpr vec4 &operator<<=(const vec4<A> &v)
    {
        x <<= v.x;
        y <<= v.y;
        z <<= v.z;
        w <<= v.w;
        return *this;
    }

    template <IsIntegerT A>
    constexpr vec4 &operator<<=(A numBits)
    {
        x <<= numBits;
        y <<= numBits;
        z <<= numBits;
        w <<= numBits;
        return *this;
    }

    // Bitwise right shift operator
    template <IsIntegerT A>
    constexpr vec4 &operator>>=(const vec4<A> &v)
    {
        x >>= v.x;
        y >>= v.y;
        z >>= v.z;
        w >>= v.w;
        return *this;
    }

    template <IsIntegerT A>
    constexpr vec4 &operator>>=(A numBits)
    {
        x >>= numBits;
        y >>= numBits;
        z >>= numBits;
        w >>= numBits;
        return *this;
    }

    // Comparison Operators
    template <IsNumberT A>
    constexpr bool operator==(const vec4<A> &v)
    {
        return this->x == v.x && this->y == v.y && this->z == v.z && this->w == v.w;
    }

    template <IsNumberT A>
    constexpr bool operator!=(const vec4<A> &v)
    {
        return !(this == v);
    }

    template <IsNumberT A>
    constexpr bool operator<(const vec4<A> &v)
    {
        if (this->x != v.x)
            return this->x < v.x;
        if (this->y != v.y)
            return this->y < v.y;
        if (this->z != v.z)
            return this->z < v.z;
        return this->w < v.w;
    }

    template <IsNumberT A>
    constexpr bool operator<=(const vec4<A> &v)
    {
        return !(this < v);
    }

    template <IsNumberT A>
    constexpr bool operator>(const vec4<A> &v)
    {
        return this < v;
    }

    template <IsNumberT A>
    constexpr bool operator>=(const vec4<A> &v)
    {
        return !(this < v);
    }

    // String / Print functions
    constexpr std::string toString() const
    {
        if constexpr (IsFloatingPointT<decltype(x)>) {
            return std::format("vec4(x: {:.5f}, y: {:.5f}, z: {:.5f}, w: {:.5f})",
                               static_cast<double>(x), static_cast<double>(y),
                               static_cast<double>(z), static_cast<double>(w));
        }
        else {
            return std::format("vec4(x: {}, y: {}, z: {}, w: {})", x, y, z, w);
        }
    }

    void print() const { std::cout << toString() << '\n'; }
};

// Friend functions
template <IsNumberT T>
constexpr vec4<T> operator+(const vec4<T> &lhs, const vec4<T> &rhs)
{
    return vec4<T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
}

template <IsNumberT T>
constexpr vec4<T> operator-(const vec4<T> &lhs, const vec4<T> &rhs)
{
    return vec4<T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.x - rhs.z, lhs.w - rhs.w);
}

template <IsNumberT T>
constexpr vec4<T> operator/(const vec4<T> &vec, float scalar)
{
    if (scalar != 0.0f) {
        return vec4<T>(vec.x / scalar, vec.y / scalar, vec.z / scalar, vec.w / scalar);
    }
    else {
        throw std::invalid_argument("Division by zero");
    }
}

template <IsNumberT T>
constexpr vec4<T> operator*(const vec4<T> &vec, float scalar)
{
    return vec4<T>(vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar);
}

// Support commutative multiplication
template <IsNumberT T>
constexpr vec4<T> operator*(float scalar, const vec4<T> &vec)
{
    return vec4<T>(vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar);
}

// Comparison Operators
template <IsNumberT T>
constexpr bool operator==(const vec4<T> &lhs, const vec4<T> &rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}

template <IsNumberT T>
constexpr bool operator!=(const vec4<T> &lhs, const vec4<T> &rhs)
{
    return !(lhs == rhs);
}

template <IsNumberT T>
constexpr bool operator<(const vec4<T> &lhs, const vec4<T> &rhs)
{
    if (lhs.x != rhs.x)
        return lhs.x < rhs.x;
    if (lhs.y != rhs.y)
        return lhs.y < rhs.y;
    if (lhs.z != rhs.z)
        return lhs.z < rhs.z;
    return lhs.w < rhs.w;
}

template <IsNumberT T>
constexpr bool operator<=(const vec4<T> &lhs, const vec4<T> &rhs)
{
    return !(rhs < lhs);
}

template <IsNumberT T>
constexpr bool operator>(const vec4<T> &lhs, const vec4<T> &rhs)
{
    return rhs < lhs;
}

template <IsNumberT T>
constexpr bool operator>=(const vec4<T> &lhs, const vec4<T> &rhs)
{
    return !(lhs < rhs);
}

// Swizzle Operators
template <IsNumberT T>
constexpr vec4<T> wzyx(const vec4<T> &v)
{
    return vec4<T>(v.w, v.z, v.x, v.y);
}

template <IsNumberT T>
constexpr vec4<T> xxxx(const vec4<T> &v)
{
    return vec4<T>(v.x, v.x, v.x, v.x);
}

template <IsNumberT T>
constexpr vec4<T> yyyy(const vec4<T> &v)
{
    return vec4<T>(v.y, v.y, v.y, v.y);
}

template <IsNumberT T>
constexpr vec4<T> zzzz(const vec4<T> &v)
{
    return vec4<T>(v.z, v.z, v.z, v.z);
}

template <IsNumberT T>
constexpr vec4<T> wwww(const vec4<T> &v)
{
    return vec4<T>(v.w, v.w, v.w, v.w);
}

using vec4f = vec4<float>;
using vec4i = vec4<int>;
using vec4u = vec4<unsigned int>;

#endif // QUIKMAFF_VEC4_HPP
