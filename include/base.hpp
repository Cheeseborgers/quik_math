#ifndef QUIKMAFF_BASE_HPP
#define QUIKMAFF_BASE_HPP

#include <climits>
#include <format>
#include <iomanip>  // std::setprecision
#include <iostream> // std::cout, std::fixed
#include <mutex>
#include <stdexcept> // for exceptions
#include <type_traits>
#include <utility>
#include <cassert>

#ifndef NDEBUG
#define QM_DEBUG
#define QM_ENABLE_ASSERTS
#endif

#define QM_ALWAYS_INLINE
#define QM_NORMALIZED_COLOURS false

// Inline
#ifdef QM_ALWAYS_INLINE
#define QM_INLINE __always_inline
#else
#define QM_INLINE inline
#endif

// Assertions
#define QM_STATIC_ASSERT(expr) static_assert(expr, "static assert failed: " #expr);

#ifdef QM_ENABLE_ASSERTS
#define QM_ASSERT(condition) assert(condition)
#else
#define QM_ASSERT(condition) ((void)0)
#endif

#include "types.hpp"

#endif // QUIKMAFF_BASE_HPP
