#ifndef QUIKMAFF_VEC4_HPP
#define QUIKMAFF_VEC4_HPP

#include "concepts.hpp"
#include "functions.hpp"
#include <string>

template <NumberType T>
struct vec2;
template <NumberType T>
struct vec3;

template <NumberType T>
struct vec4 {
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
        : x{static_cast<T>(0.0)}, y{static_cast<T>(0.0)}, z{static_cast<T>(0.0)}, w{static_cast<T>(0.0)}
    {
    }

    // Conversion scalar constructors
    template <NumberType X, NumberType Y, NumberType Z, NumberType W>
    constexpr vec4(X _x, Y _y, Z _z, W _w)
        : x(static_cast<T>(_x)), y(static_cast<T>(_y)), z(static_cast<T>(_z)), w(static_cast<T>(_w))
    {
    }

    // Conversion vector constructors
    template <NumberType X, NumberType A, NumberType B>
    constexpr vec4(vec2<X> const &_xy, A _z, B _w)
        : x(static_cast<T>(_xy.x)),
          y(static_cast<T>(_xy.y)),
          z(static_cast<T>(_z)),
          w(static_cast<T>(_w))
    {
    }

    template <NumberType A, NumberType X, NumberType B>
    constexpr vec4(A _x, vec2<X> const &_yz, B _w)
        : x(static_cast<T>(_x)),
          y(static_cast<T>(_yz.x)),
          z(static_cast<T>(_yz.y)),
          w(static_cast<T>(_w))
    {
    }

    template <NumberType A, NumberType B, NumberType X>
    constexpr vec4(A _x, B _y, vec2<X> const &_zw)
        : x(static_cast<T>(_x)),
          y(static_cast<T>(_y)),
          z(static_cast<T>(_zw.x)),
          w(static_cast<T>(_zw.y))
    {
    }

    template <NumberType X, NumberType A>
    constexpr vec4(vec3<X> const &_xyz, A _w)
        : x(static_cast<T>(_xyz.x)),
          y(static_cast<T>(_xyz.y)),
          z(static_cast<T>(_xyz.z)),
          w(static_cast<T>(_w))
    {
    }

    template <NumberType A, NumberType X>
    constexpr vec4(A _x, vec3<X> const &_yzw)
        : x(static_cast<T>(_x)),
          y(static_cast<T>(_yzw.x)),
          z(static_cast<T>(_yzw.y)),
          w(static_cast<T>(_yzw.z))
    {
    }

    template <NumberType A, NumberType B>
    constexpr vec4(vec2<A> const &_xy, vec2<B> const &_zw)
        : x(static_cast<T>(_xy.x)),
          y(static_cast<T>(_xy.y)),
          z(static_cast<T>(_zw.x)),
          w(static_cast<T>(_zw.y))
    {
    }
    template <NumberType X>
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

    static constexpr std::size_t length() { return 4; }
    static constexpr std::size_t size() { return sizeof(vec4); }

    // Component accesses
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
            case 3:
                return w;
            default:
                return static_cast<T>(0.0);
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
            case 3:
                return w;
        }
    }

    // String / Print functions
    constexpr std::string toString() const
    {
        if constexpr (FloatingPointType<decltype(x)>) {
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

using vec4f = vec4<float>;
using vec4i = vec4<int>;

#endif // QUIKMAFF_VEC4_HPP
