#pragma once
// Binary Exponentiation
#include <cstdint>
#include <functional>
#include <type_traits>

template <typename T, auto f = std::multiplies()>
constexpr static T qpow(T a, int64_t b) {
    T res;
    if constexpr (std::is_arithmetic_v<T>) {
        res = 1;
    } else {
        res = a.identity();
    }
    while (b) {
        if (b & 1) {
            res = f(res, a);
        }
        b >>= 1;
        a = f(a, a);
    }
    return res;
}
