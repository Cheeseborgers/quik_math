#ifndef QUIKMAFF_TYPES_HPP
#define QUIKMAFF_TYPES_HPP

#include <cmath>
#include <cstdint>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using f32 = float;
using f64 = double;
using f128 = long double;

namespace qm {

using i_least8 = signed char;
using i_least16 = signed short;
using i_least32 = signed int;
using i_least64 = signed long;

using u_least8 = unsigned char;
using u_least16 = unsigned short;
using u_least32 = unsigned int;
using u_least64 = unsigned long;

} // namespace qm

#endif // QUIKMAFF_TYPES_HPP