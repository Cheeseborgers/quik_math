#ifndef QUIKMAFF_FUNCTIONS_HPP
#define QUIKMAFF_FUNCTIONS_HPP

#include <cmath>

#include "concepts.hpp"
#include "constants.hpp"

namespace qm {

template<IsNumberT T>
bool isnan(T x)
{
   return std::isnan(x);
}

template<IsNumberT T>
bool isinf(T x)
{
    return std::isinf(x);
}

/**
 * @brief Returns the largest possible value for type T.
 *
 * This function returns the maximum representable value for the specified data type T.
 *
 * @tparam T The data type.
 * @return The maximum value representable by type T.
 *
 * Example:
 * ```
 * int maxInt = maxValue<int>();
 * // maxInt is the largest possible value for the int data type.
 * ```
 */
template <IsNumberT T>
constexpr auto maxValue() -> T
{
    return std::numeric_limits<T>::max();
}

/**
 * @brief Returns the smallest possible value for type T.
 *
 * This function returns the minimum finite representable value for the specified data type T.
 *
 * @tparam T The data type.
 * @return The minimum value representable by type T.
 *
 * Note: The behavior may vary slightly for different types, and some types, like unsigned
 * integers, do not have a meaningful "minimum" value in the same sense as signed integers or
 * floating-point types.
 *
 * Example:
 * ```
 * int minInt = minValue<int>();
 * // minInt is the smallest possible value for the int data type.
 * ```
 */
template <IsNumberT T>
constexpr auto minValue() -> T
{
    return std::numeric_limits<T>::min();
}

/**
 * @brief Returns the number of bits used to represent type T.
 *
 * This function returns the number of bits required to represent values of the
 * specified integer data type T.
 *
 * @tparam T The data type.
 * @return The number of bits used to represent type T.
 *
 * Example:
 * ```
 * int numBitsInt = numBits<int>();
 * // numBitsInt is the number of bits used to represent an int.
 * ```
 */
template <IsIntegerT T>
constexpr auto numBits() -> int
{
    return std::numeric_limits<T>::digits;
}

/**
 * @brief Converts a value from kilobytes (KB) to bytes.
 *
 * This function converts a value from kilobytes to bytes.
 *
 * @tparam T The type of the input value.
 * @param x The value to convert.
 * @return The converted value in bytes.
 *
 * Example:
 * ```
 * u64 bytes = kb<int>(256);
 * // bytes is 256 * 1024, i.e., 262144.
 * ```
 */
template <IsIntegerT T>
constexpr u64 kb(T x)
{
    return static_cast<u64>(1024) * x;
}

/**
 * @brief Converts a value from megabytes (MB) to bytes.
 *
 * This function converts a value from megabytes to bytes.
 *
 * @tparam T The type of the input value.
 * @param x The value to convert.
 * @return The converted value in bytes.
 *
 * Example:
 * ```
 * u64 bytes = mb<int>(128);
 * // bytes is 128 * 1024 * 1024, i.e., 134217728.
 * ```
 */
template <IsIntegerT T>
constexpr u64 mb(T x)
{
    return static_cast<u64>(1024) * KB(x);
}

/**
 * @brief Converts a value from gigabytes (GB) to bytes.
 *
 * This function converts a value from gigabytes to bytes.
 *
 * @tparam T The type of the input value.
 * @param x The value to convert.
 * @return The converted value in bytes.
 *
 * Example:
 * ```
 * u64 bytes = gb<int>(4);
 * // bytes is 4 * 1024 * 1024 * 1024, i.e., 4294967296.
 * ```
 */
template <IsIntegerT T>
constexpr u64 gb(T x)
{
    return static_cast<u64>(1024) * MB(x);
}

/**
 * @brief Calculate the absolute value of a numeric type.
 *
 * This function calculates the absolute value of the input value, making it
 * positive (or zero if it's already non-negative).
 *
 * @tparam T The numeric type for which the absolute value is calculated.
 * @param value The input value.
 * @return The absolute value of the input value.
 *
 * Example:
 * ```
 * int absoluteInt = abs(-5);
 * // absoluteInt is 5.
 *
 * double absoluteDouble = abs(-3.14);
 * // absoluteDouble is 3.14.
 * ```
 */

template <typename T>
constexpr T sin(T angle)
{
    return std::sin(angle);
}

template <typename T>
constexpr T cos(T angle)
{
    return std::cos(angle);
}

template <typename T>
constexpr T tan(T angle)
{
    return std::tan(angle);
}

template <typename T>
T abs(T value)
{
    //const int y = x >> (sizeof(int) * 8 - 1);
    //return (x ^ y) - y;
}

/**
 * @brief Calculate the square root of a numeric type.
 *
 * This function calculates the square root of the input value using the
 * `std::sqrt` function from the C++ Standard Library.
 *
 * @tparam T The numeric type for which the square root is calculated.
 * @param value The input value.
 * @return The square root of the input value.
 *
 * Example:
 * ```
 * double squareRoot = sqrt(16.0);
 * // squareRoot is 4.0.
 *
 * float squareRootFloat = sqrt(25.0f);
 * // squareRootFloat is 5.0f.
 * ```
 */
template <IsNumberT T>
constexpr T sqrt(T value)
{
    return std::sqrt(value);
}

/**
 * @brief Calculates the maximum of two values.
 *
 * This function compares two values of the same data type and returns the greater of the two.
 *
 * @tparam T The data type of the values.
 * @param a The first value.
 * @param b The second value.
 * @return The greater of the two input values.
 *
 * Example:
 * ```
 * int maxVal = max(5, 8);
 * // maxVal is 8, which is the greater value.
 * ```
 */
template <IsNumberT T>
constexpr T max(T a, T b)
{
    return (a < b) ? b : a;
}

/**
 * @brief Calculates the minimum of two values.
 *
 * This function compares two values of the same data type and returns the smaller of the two.
 *
 * @tparam T The data type of the values.
 * @param a The first value.
 * @param b The second value.
 * @return The smaller of the two input values.
 *
 * Example:
 * ```
 * double minVal = min(3.14, 2.71);
 * // minVal is 2.71, which is the smaller value.
 * ```
 */
template <typename T>
constexpr T min(T a, T b)
{
    return (b < a) ? b : a;
}

/**
 * @brief Calculates the maximum value among a list of values.
 *
 * This function takes an initializer list of values and returns the largest value among them.
 *
 * @tparam T The data type of the values.
 * @param values The list of values.
 * @return The larger value among the input values.
 *
 * Example:
 * ```
 * std::initializer_list<int> values = {5, 8, 2, 10};
 * int maxValue = max(values);
 * // maxValue is 10, which is the largest value in the list.
 * ```
 */
template <IsNumberT T>
constexpr T max(std::initializer_list<T> values)
{
    T maxValue = *values.begin();
    for (const T &value : values) {
        if (value > maxValue) {
            maxValue = value;
        }
    }
    return maxValue;
}

/**
 * @brief Calculates the minimum value among a list of values.
 *
 * This function takes an initializer list of values and returns the smallest value among them.
 *
 * @tparam T The data type of the values.
 * @param values The list of values.
 * @return The minimum value among the input values.
 *
 * Example:
 * ```
 * std::initializer_list<double> values = {3.14, 2.71, 1.0, 5.0};
 * double minValue = min(values);
 * // minValue is 1.0, which is the smallest value in the list.
 * ```
 */
template <IsNumberT T>
constexpr T min(std::initializer_list<T> values)
{
    T minValue = *values.begin();
    for (const T &value : values) {
        if (value < minValue) {
            minValue = value;
        }
    }
    return minValue;
}

/**
 * @brief Clamp a value within a specified range.
 *
 * This function takes a value, a minimum bound, and a maximum bound and ensures
 * that the value falls within the specified range. If the value is less than the
 * minimum bound, it is clamped to the minimum bound. If the value is greater than
 * the maximum bound, it is clamped to the maximum bound. If the value is within
 * the range, it remains unchanged.
 *
 * @tparam T The numeric type of the value, which should satisfy the NumberType concept.
 * @param value The value to be clamped.
 * @param minVal The minimum bound.
 * @param maxVal The maximum bound.
 * @return The clamped value within the specified range.
 *
 * Example:
 * ```
 * double clampedValue = clamp(5.0, 0.0, 10.0);
 * // clampedValue is 5.0 because it falls within the range [0.0, 10.0].
 * ```
 */
template <IsNumberT T>
constexpr T clamp(const T &value, const T &minVal, const T &maxVal)
{
    if (value < minVal) {
        return minVal;
    }
    else if (value > maxVal) {
        return maxVal;
    }
    else {
        return value;
    }
}

/**
 * @brief Calculate the percentage of a value relative to a total.
 *
 * This function calculates the percentage of a value relative to a total. It takes
 * a value and a total, where the value represents a portion of the total, and it
 * returns the percentage of the value with respect to the total. If the total is
 * zero, it handles division by zero by returning 0.0.
 *
 * @tparam T The numeric type of the value and total, which should satisfy the FloatingPointType
 * concept.
 * @param value The value for which the percentage is calculated.
 * @param total The total value to which the percentage is relative.
 * @return The calculated percentage as a floating-point value.
 *
 * Example:
 * ```
 * double result = percentage(25.0, 100.0);
 * // result is 25.0 because 25.0 is 25% of 100.0.
 * ```
 */
template <IsFloatingPointT T>
constexpr T percentage(T value, T total)
{
    if (total == static_cast<T>(0.0)) {
        // Handle division by zero by returning 0.0
        return static_cast<T>(0.0);
    }

    return (value / total) * static_cast<T>(100.0);
}

/**
 * @brief Linearly interpolates between two values.
 *
 * This function performs linear interpolation between two values based on an interpolation
 * parameter 't'.
 *
 * @tparam ValueType The type of values to interpolate.
 * @tparam InterpolationType The type of the interpolation parameter.
 * @param startValue The starting value for interpolation.
 * @param endValue The ending value for interpolation.
 * @param t The interpolation parameter (0.0 for startValue, 1.0 for endValue).
 * @return The interpolated value between startValue and endValue.
 *
 * Example:
 * ```
 * float interpolatedValue = lerp(10.0f, 20.0f, 0.5f);
 * // interpolatedValue is 15.0f, which is halfway between 10.0f and 20.0f.
 * ```
 */
template <typename ValueType, typename InterpolationType>
constexpr ValueType lerp(const ValueType &startValue, const ValueType &endValue,
                         InterpolationType t)
{
    t = clamp(t, static_cast<InterpolationType>(0), static_cast<InterpolationType>(1));
    return startValue * (static_cast<ValueType>(1) - t) + endValue * t;
}

/**
 * @brief Corrects degrees to be within the range [0, 360).
 *
 * This function takes an input angle in degrees and ensures that it falls within the range [0,
 * 360).
 *
 * @param degrees The input angle in degrees.
 * @return The corrected angle in degrees.
 *
 * Example:
 * ```
 * float correctedAngle = correctDegrees(450.0f);
 * // correctedAngle is 90.0f because it wraps around to the range [0, 360).
 * ```
 */
constexpr f32 correctDegrees(f32 degrees) { return std::fmod(degrees, 360.0f); }

/**
 * @brief Converts radians to degrees.
 *
 * This function converts an angle from radians to degrees.
 *
 * @param radians The radians to convert.
 * @return The result in degrees.
 *
 * Example:
 * ```
 * float degrees = radiansToDegrees(1.5708f);
 * // degrees is approximately 90.0f, which is pi/2 radians in degrees.
 * ```
 */
template <typename T>
constexpr T radiansToDegrees(T radians)
{
    return radians * static_cast<T>(180.0) / static_cast<T>(qm::pi<T>);
}

/**
 * @brief Converts degrees to radians.
 *
 * This function converts an angle from degrees to radians.
 *
 * @param degrees The degrees to convert.
 * @return The result in radians.
 *
 * Example:
 * ```
 * float radians = degreesToRadians(90.0f);
 * // radians is approximately 1.5708f, which is 90 degrees in radians.
 * ```
 */
template <typename T>
constexpr f32 degreesToRadians(f32 degrees)
{
    return degrees * static_cast<T>(qm::pi<T>) / static_cast<T>(180.0);
}

/**
 * @brief Compares two floating-point values for approximate equality.
 *
 * This function compares two floating-point values for approximate equality within a small epsilon
 * range.
 *
 * @tparam T The type of values to compare.
 * @param x The first value to compare.
 * @param y The second value to compare.
 * @return `true` if the values are approximately equal, `false` otherwise.
 *
 * Example:
 * ```
 * bool isEqual = compare(1.0f, 1.00001f);
 * // isEqual is true because the values are approximately equal within a small epsilon.
 * ```
 */
template <typename T>
constexpr bool compare(const T x, const T y)
{
    return abs(x - y) <= qm::epsilon<T> * max(static_cast<T>(1.0), max(abs(x), abs(y)));
}

/**
 * @brief Calculates the Euclidean distance between two 3D points.
 *
 * This function calculates the Euclidean distance between two 3D points represented by their
 * coordinates (x1, y1, z1) and (x2, y2, z2).
 *
 * @tparam T The type of the coordinates.
 * @param x1 The x-coordinate of the first point.
 * @param y1 The y-coordinate of the first point.
 * @param z1 The z-coordinate of the first point.
 * @param x2 The x-coordinate of the second point.
 * @param y2 The y-coordinate of the second point.
 * @param z2 The z-coordinate of the second point.
 * @return The distance between the two points.
 *
 * Example:
 * ```
 * float distance = distance(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);
 * // distance is approximately 5.1962, which is the Euclidean distance between the two points.
 * ```
 */
template <typename T>
constexpr f32 distance(T x1, T y1, T z1, T x2, T y2, T z2)
{
    T dx = x2 - x1;
    T dy = y2 - y1;
    T dz = z2 - z1;

    return sqrt(dx * dx + dy * dy + dz * dz);
}

} // namespace qm

#endif // QUIKMAFF_FUNCTIONS_HPP