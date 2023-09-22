#ifndef QUIKMAFF_CONCEPTS_HPP
#define QUIKMAFF_CONCEPTS_HPP

#include "base.hpp"

/**
 * @brief Concept that checks if a type is a floating-point type.
 * @tparam T The type to check.
 */
template <typename T>
concept FloatingPointType = std::is_floating_point_v<T>;

/**
 * @brief Concept that checks if a type is a integral type.
 * @tparam T The type to check.
 */
template <typename T>
concept IntegerType = std::is_integral_v<T>;

/**
 * @brief Concept that checks if a type is an integer or floating-point type.
 * @tparam T The type to check.
 */
template <typename T>
concept NumberType = std::is_arithmetic_v<T>;

#endif // QUIKMAFF_CONCEPTS_HPP