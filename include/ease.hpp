#ifndef QUIKMAFF_EASE_HPP
#define QUIKMAFF_EASE_HPP

#include "concepts.hpp"
#include <functional>

/**
 * @brief Enumeration of easing types that can be used with the easing functions.
 */
enum class EaseType {
    Linear,       ///< Linear easing
    InQuad,       ///< Quadratic ease-in
    OutQuad,      ///< Quadratic ease-out
    InOutQuad,    ///< Quadratic ease-in and ease-out
    InCubic,      ///< Cubic ease-in
    OutCubic,     ///< Cubic ease-out
    InOutCubic,   ///< Cubic ease-in and ease-out
    InQuartic,    ///< Quartic ease-in
    OutQuartic,   ///< Quartic ease-out
    InOutQuartic, ///< Quartic ease-in and ease-out
    InQuintic,    ///< Quintic ease-in
    OutQuintic,   ///< Quintic ease-out
    InOutQuintic, ///< Quintic ease-in and ease-out
    Elastic,      ///< Elastic easing
    Bounce,       ///< Bounce easing
};

// Easing functions
template <FloatingPointType T>
constexpr T linear(T t)
{
    return t;
}

template <FloatingPointType T>
constexpr T easeInQuad(T t)
{
    return t * t;
}

template <FloatingPointType T>
constexpr T easeOutQuad(T t)
{
    return 1 - (1 - t) * (1 - t);
}

template <FloatingPointType T>
constexpr T easeInOutQuad(T t)
{
    if (t < 0.5) {
        return 2 * t * t;
    }
    else {
        return 1 - pow(-2 * t + 2, 2) / 2;
    }
}

template <FloatingPointType T>
constexpr T easeInCubic(T t)
{
    return t * t * t;
}

template <FloatingPointType T>
constexpr T easeOutCubic(T t)
{
    return 1 - pow(1 - t, 3);
}

template <FloatingPointType T>
constexpr T easeInOutCubic(T t)
{

    if (t < 0.5) {
        return 4 * t * t * t;
    }
    else {
        return 1 - pow(-2 * t + 2, 3) / 2;
    }
}

template <FloatingPointType T>
constexpr T easeInQuartic(T t)
{
    return t * t * t * t;
}

template <FloatingPointType T>
constexpr T easeOutQuartic(T t)
{
    return 1 - pow(1 - t, 4);
}

template <FloatingPointType T>
constexpr T easeInOutQuartic(T t)
{
    if (t < 0.5) {
        return 8 * t * t * t * t;
    }
    else {
        return 1 - pow(-2 * t + 2, 4) / 2;
    }
}

template <FloatingPointType T>
constexpr T easeInQuintic(T t)
{
    return t * t * t * t * t;
}

template <FloatingPointType T>
constexpr T easeOutQuintic(T t)
{
    return 1 - pow(1 - t, 5);
}

template <FloatingPointType T>
constexpr T easeInOutQuintic(T t)
{
    if (t < 0.5) {
        return 16 * t * t * t * t * t;
    }
    else {
        return 1 - pow(-2 * t + 2, 5) / 2;
    }
}

template <FloatingPointType T>
constexpr T elastic(T t)
{
    constexpr T c4 = (2 * std::numbers::pi) / 3.0;
    return t == 0 ? 0 : t == 1 ? 1 : pow(2, -10 * t) * sin((t * 10 - 0.75) * c4) + 1;
}

template <FloatingPointType T>
constexpr T bounce(T t)
{
    if (t < 1 / 2.75) {
        return 7.5625 * t * t;
    }
    else if (t < 2 / 2.75) {
        return 7.5625 * (t -= 1.5 / 2.75) * t + 0.75;
    }
    else if (t < 2.5 / 2.75) {
        return 7.5625 * (t -= 2.25 / 2.75) * t + 0.9375;
    }
    else {
        return 7.5625 * (t -= 2.625 / 2.75) * t + 0.984375;
    }
}

/**
 * @brief Get the easing function based on the specified EaseType.
 *
 * @tparam T The floating-point type for which the easing function is returned.
 * @param easeType The desired EaseType.
 * @return A std::function representing the easing function.
 *
 * Example:
 * ```
 * double t = 0.5;
 * std::function<double(double)> easingFunc = Ease::getFunction(EaseType::OutCubic);
 * double result = easingFunc(t);
 * // Use the result for your application.
 * ```
 */
template <FloatingPointType T>
constexpr std::function<T(T)> getEaseFunction(EaseType easeType)
{
    switch (easeType) {
        case EaseType::InQuad:
            return [](T t) { return easeInQuad(t); };
        case EaseType::OutQuad:
            return [](T t) { return easeOutQuad(t); };
        case EaseType::InOutQuad:
            return [](T t) { return easeInOutQuad(t); };
        case EaseType::InCubic:
            return [](T t) { return easeInCubic(t); };
        case EaseType::OutCubic:
            return [](T t) { return easeOutCubic(t); };
        case EaseType::InOutCubic:
            return [](T t) { return easeInOutCubic(t); };
        case EaseType::InQuartic:
            return [](T t) { return easeInQuartic(t); };
        case EaseType::OutQuartic:
            return [](T t) { return easeOutCubic(t); };
        case EaseType::InOutQuartic:
            return [](T t) { return easeInOutQuartic(t); };
        case EaseType::InQuintic:
            return [](T t) { return easeInQuintic(t); };
        case EaseType::OutQuintic:
            return [](T t) { return easeOutQuintic(t); };
        case EaseType::InOutQuintic:
            return [](T t) { return easeInOutQuintic(t); };
        case EaseType::Elastic:
            return [](T t) { return elastic(t); };
        case EaseType::Bounce:
            return [](T t) { return bounce(t); };
        case EaseType::Linear:
        default:
            return [](T t) { return t; }; // Default to linear
    }
}

#endif // QUIKMAFF_EASE_HPP
