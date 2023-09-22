#ifndef QUIKMAFF_VEC2_HPP
#define QUIKMAFF_VEC2_HPP

#include "concepts.hpp"
#include "functions.hpp"
#include <string>

template <NumberType T>
struct vec3;
template <NumberType T>
struct vec4;

template <NumberType T>
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
    template <NumberType X, NumberType Y>
    constexpr vec2(X _x, Y _y) : x(static_cast<T>(_x)), y(static_cast<T>(_y))
    {
    }

    // Conversion vector constructors
    template <NumberType X>
    constexpr vec2(vec2<X> const &v) : x(static_cast<T>(v.x)), y(static_cast<T>(v.y))
    {
    }

    template <NumberType X>
    constexpr vec2(vec3<X> const &v) : x(static_cast<T>(v.x)), y(static_cast<T>(v.y))
    {
    }

    template <NumberType X>
    constexpr vec2(vec4<X> const &v) : x(static_cast<T>(v.x)), y(static_cast<T>(v.y))
    {
    }

    // Static factory methods
    static constexpr vec2 zero() { return vec2(static_cast<T>(0.0)); }
    static constexpr vec2 ones() { return vec2(static_cast<T>(1.0)); }

    static constexpr std::size_t length() { return 2; }
    static constexpr std::size_t size() { return sizeof(vec2); }

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
        }
    }

    // String / Print functions
    constexpr std::string toString() const
    {
        if constexpr (FloatingPointType<decltype(x)>) {
            return std::format("vec2(x: {:.5f}, y: {:.5f})", static_cast<double>(x),
                               static_cast<double>(y));
        }
        else {
            return std::format("vec2(x: {}, y: {})", x, y);
        }
    }

    void print() const { std::cout << toString() << '\n'; }
};

using vec2f = vec2<float>;
using vec2i = vec2<int>;

#endif // QUIKMAFF_VEC2_HPP
