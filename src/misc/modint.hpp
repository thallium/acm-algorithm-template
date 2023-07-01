#pragma once
// Modint
#include <limits>
#include <type_traits>
#include <iostream>
#include "misc/bin_expo.hpp"

template <typename T, T MOD>
struct ModInt {
    using prod_type = std::conditional_t<std::numeric_limits<T>::digits <= 32, uint64_t, __uint128_t>;
    T val;
    constexpr ModInt(const int64_t v = 0) : val(v % MOD) { if (val < 0) val += MOD; }
    constexpr ModInt operator+() const { return ModInt(val); }
    constexpr ModInt operator-() const { return ModInt(MOD - val); }
    constexpr ModInt inv() const {
        return qpow(*this, MOD - 2);
    }
    constexpr friend ModInt operator+(ModInt lhs, const ModInt rhs) { return lhs += rhs; }
    constexpr friend ModInt operator-(ModInt lhs, const ModInt rhs) { return lhs -= rhs; }
    constexpr friend ModInt operator*(ModInt lhs, const ModInt rhs) { return lhs *= rhs; }
    constexpr friend ModInt operator/(ModInt lhs, const ModInt rhs) { return lhs /= rhs; }
    constexpr ModInt &operator+=(const ModInt x) {
        if ((val += x.val) >= MOD)
            val -= MOD;
        return *this;
    }
    constexpr ModInt &operator-=(const ModInt x) {
        if ((val -= x.val) < 0)
            val += MOD;
        return *this;
    }
    constexpr ModInt &operator*=(const ModInt x) {
        val = prod_type(val) * x.val % MOD;
        return *this;
    }
    constexpr ModInt &operator/=(const ModInt x) { return *this *= x.inv(); }
    bool operator==(const ModInt b) const { return val == b.val; }
    bool operator!=(const ModInt b) const { return val != b.val; }
    friend std::istream &operator>>(std::istream &is, ModInt &x) noexcept {
        return is >> x.val;
    }
    friend std::ostream &operator<<(std::ostream &os, const ModInt x) noexcept {
        return os << x.val;
    }
    constexpr static ModInt identity() { return 1; }
    constexpr ModInt pow(int64_t p) {
        return qpow(*this, p);
    }
};
using ModInt1000000007 = ModInt<int, 1'000'000'007>;
using ModInt998244353 = ModInt<int, 998244353>;
