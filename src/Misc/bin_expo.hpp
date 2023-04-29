#pragma once
// Binary Exponentiation
#include <cstdint>
#include <type_traits>

template <typename T>
constexpr static T qpow(T a, int64_t b) {
    T res;
    if constexpr (std::is_arithmetic_v<T>) {
        res = 1;
    } else {
        res = T::identity();
    }
    while (b) {
        if (b & 1) {
            res *= a;
        }
        b >>= 1;
        a *= a;
    }
    return res;
}
