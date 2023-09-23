#ifndef QUIKMAFF_CONCEPTS_HPP
#define QUIKMAFF_CONCEPTS_HPP

#include "base.hpp"

// Template meta-variable that checks if a type is the same as 'bool'
template <typename T>
constexpr bool IsBooleanT = std::is_same_v<T, bool>;

/**
 * @brief Concept that checks if a type is a floating-point type.
 * @tparam T The type to check.
 */
template <typename T>
concept IsFloatingPointT = std::numeric_limits<T>::is_iec559;

/**
 * @brief Concept that checks if a type is an integral type.
 * @tparam T The type to check.
 */
template <typename T>
concept IsIntegerT = std::is_integral_v<T>;

/**
 * @brief Concept that checks if a type is an integer or floating-point type.
 * @tparam T The type to check.
 */
template <typename T>
concept IsNumberT = std::is_arithmetic_v<T>;

/**
 * @brief Concept that checks if a type is a floating-point vector of a specific size.
 * @tparam T The type to check.
 * @tparam Size The required size of the vector.
 */
template <typename T, std::size_t Size>
concept IsFloatVec = IsFloatingPointT<T> && std::tuple_size_v<T> == Size;

/**
 * @brief Concept that checks if a type is an integral vector of a specific size.
 * @tparam T The type to check.
 * @tparam Size The required size of the vector.
 */
template <typename T, std::size_t Size>
concept IsIntegerVec = IsIntegerT<T> && std::tuple_size_v<T> == Size;

/**
 * @brief Concept that checks if a type is a numeric (integer or floating-point) vector of a
 * specific size.
 * @tparam T The type to check.
 * @tparam Size The required size of the vector.
 */
template <typename T, std::size_t Size>
concept IsNumberVec = IsNumberT<T> && std::tuple_size_v<T> == Size;

/**
 * @brief Concept that checks if a type is a boolean vector of a specific size.
 * @tparam T The type to check.
 * @tparam Size The required size of the vector.
 */
template <typename T, std::size_t Size>
concept IsBoolVec = IsBooleanT<T> && std::tuple_size_v<T> == Size;

#endif // QUIKMAFF_CONCEPTS_HPP