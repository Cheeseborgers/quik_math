#ifndef QUIKMAFF_MAT4_HPP
#define QUIKMAFF_MAT4_HPP

#include <array>
#include <cstring>

#include "functions.hpp"

//  OpenGL typically follows a column-major ordering convention for matrices
class mat4 {
public:
    constexpr mat4() { m_data.fill({0.0f, 0.0f, 0.0f, 0.0f}); }
    constexpr mat4(float value) { m_data.fill({value, value, value, value}); }

    constexpr mat4(float m00, float m01, float m02, float m03, float m10, float m11, float m12,
                   float m13, float m20, float m21, float m22, float m23, float m30, float m31,
                   float m32, float m33)
    {
        m_data = {{{m00, m01, m02, m03},
                   {m10, m11, m12, m13},
                   {m20, m21, m22, m23},
                   {m30, m31, m32, m33}}};
    }

    constexpr mat4(const float data[16])
    {
        // Copy the data into the matrix
        for (std::size_t row = 0; row < 4; ++row) {
            for (std::size_t col = 0; col < 4; ++col) {
                m_data[row][col] = data[row * 4 + col];
            }
        }
    }

    constexpr mat4(const mat4 &other) { m_data = other.m_data; }

    // Get a specific element from the matrix
    constexpr float &operator()(std::size_t row, std::size_t col) { return m_data[row][col]; }

    // Get a specific element from the matrix (const version)
    const float &operator()(std::size_t row, std::size_t col) const { return m_data[row][col]; }

    static constexpr mat4 identity()
    {
        return mat4{1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
    }

    constexpr void setAsIdentity()
    {
        m_data = {{{1.0f, 0.0f, 0.0f, 0.0f},
                   {0.0f, 1.0f, 0.0f, 0.0f},
                   {0.0f, 0.0f, 1.0f, 0.0f},
                   {0.0f, 0.0f, 0.0f, 1.0f}}};
    }

    mat4 operator*(const mat4 &other) const
    {
        mat4 result;

        for (int col = 0; col < 4; ++col) {
            for (int row = 0; row < 4; ++row) {
                float sum = 0.0f;
                for (int i = 0; i < 4; ++i) {
                    sum += other(i, col) * m_data[row][i];
                }
                result(row, col) = sum;
            }
        }

        return result;
    }

    mat4 operator+(const mat4 &other) const
    {
        mat4 result;

        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 4; ++col) {
                result(row, col) = m_data[row][col] + other(row, col);
            }
        }

        return result;
    }

    mat4 operator-(const mat4 &other) const
    {
        mat4 result;

        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 4; ++col) {
                result(row, col) = m_data[row][col] - other(row, col);
            }
        }

        return result;
    }

    mat4 operator*(float scalar) const
    {
        mat4 result;

        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 4; ++col) {
                result(row, col) = m_data[row][col] * scalar;
            }
        }

        return result;
    }

    mat4 translation(float x, float y, float z)
    {
        mat4 result;
        result(0, 3) = x;
        result(1, 3) = y;
        result(2, 3) = z;
        return result;
    }

    // ===============================================================================

    // -- Unary arithmetic operators --
    mat4 &operator=(const mat4 &m)
    {
        //std::memcpy(m_data, m.m_data, 16 * sizeof(valType));
        return *this;
    }

    mat4 &operator+=(const mat4 &m)
    {
        //m_data[0] += m.m_data[0];
        //m_data[1] += m.m_data[1];
        //m_data[2] += m.m_data[2];
        //m_data[3] += m.m_data[3];
        return *this;
    }

    mat4 &operator-=(const mat4 &m)
    {
        //m_data[0] -= m.m_data[0];
        //m_data[1] -= m.m_data[1];
        //m_data[2] -= m.m_data[2];
        //m_data[3] -= m.m_data[3];
        return *this;
    }

    mat4 &operator*=(const mat4 &s)
    {
        //m_data[0] *= s;
        //m_data[1] *= s;
        //m_data[2] *= s;
        //m_data[3] *= s;
        return *this;
    }

    //mat4 &operator*=(const mat4 &m) { return (*this = *this * m); }

    mat4 &operator/=(const mat4 &s)
    {
        //m_data[0] /= s;
        //m_data[1] /= s;
        //m_data[2] /= s;
        //m_data[3] /= s;
        return *this;
    }

    //mat4 &operator/=(const mat4 &m) { return *this *= inverse(m); }

    // -- Increment and decrement operators --

    mat4 &operator++()
    {
        //++m_data[0];
        //++m_data[1];
        //++m_data[2];
        //++m_data[3];
        return *this;
    }

    mat4 &operator--()
    {
        //--m_data[0];
        //--m_data[1];
        //--m_data[2];
        //--m_data[3];
        return *this;
    }

    mat4 operator++(int)
    {
        mat4 Result(*this);
        ++*this;
        return Result;
    }

    mat4 operator--(int)
    {
        mat4 Result(*this);
        --*this;
        return Result;
    }

    // ===============================================================================

    // Function to print all values of the mat4
    constexpr void print() const
    {
        for (std::size_t row = 0; row < 4; ++row) {
            for (std::size_t col = 0; col < 4; ++col) {
                std::cout << m_data[row][col] << " ";
            }
            std::cout << std::endl; // Start a new line for the next row
        }
    }

private:
    std::array<std::array<float, 4>, 4> m_data;
};

#endif // QUIKMAFF_MAT4_HPP