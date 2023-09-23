#ifndef QUIKMAFF_CONSTANTS_HPP
#define QUIKMAFF_CONSTANTS_HPP

#include "concepts.hpp"

namespace qm {
/**
 * Value of Pi constant.
 */
template <IsFloatingPointT T>
constexpr T pi{std::numbers::pi_v<T>};

/**
 * A small positive value representing the machine epsilon.
 */
template <IsFloatingPointT T>
constexpr float epsilon{std::numeric_limits<T>::epsilon()};

} // namespace qm

#endif // QUIKMAFF_CONSTANTS_HPP
