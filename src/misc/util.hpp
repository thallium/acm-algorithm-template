#pragma once
#if __cplusplus == 202002
#include <bit>
template<typename T>
constexpr T lg(T x) {
    return std::bit_width(x) - 1;
}

template<typename T>
constexpr T ceil_lg(T x) {
    return std::countr_zero(std::bit_ceil(x));
}
#else
constexpr unsigned lg(int x) {
    return sizeof(int) * 8 - 1 - __builtin_clz(x);
}
constexpr unsigned lg(unsigned int x) {
    return sizeof(unsigned) * 8 - 1 - __builtin_clz(x);
}
constexpr unsigned lg(long x) {
    return sizeof(long) * 8 - 1 - __builtin_clzl(x);
}
constexpr unsigned lg(unsigned long x) {
    return sizeof(unsigned long) * 8 - 1 - __builtin_clzl(x);
}
constexpr unsigned lg(long long x) {
    return sizeof(long long) * 8 - 1 - __builtin_clzll(x);
}
constexpr unsigned lg(unsigned long long x) {
    return sizeof(unsigned long long) * 8 - 1 - __builtin_clzll(x);
}

constexpr unsigned ceil_lg(int n) {
    return n == 0 ? 0 : 32 - __builtin_clz(n - 1);
}
#endif
