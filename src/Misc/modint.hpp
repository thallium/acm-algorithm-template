#include <type_traits>
#include <iostream>

template <typename T, T MOD>
struct ModInt {
    using prod_type = std::conditional_t<std::is_same_v<T, int>, long long, __int128>;
    T val;
    ModInt(const prod_type v = 0) : val(v % MOD) { if (val < 0) val += MOD; };
    ModInt operator+() const { return ModInt(val); }
    ModInt operator-() const { return ModInt(MOD - val); }
    ModInt inv() const {
        auto a = val, m = MOD, u = 0, v = 1;
        while (a != 0) {
            auto t = m / a;
            m -= t * a;
            std::swap(a, m);
            u -= t * v;
            std::swap(u, v);
        }
        assert(m == 1);
        return u;
    }
    ModInt pow(prod_type n) const {
        auto x = ModInt(1);
        auto b = *this;
        while (n > 0) {
            if (n & 1)
                x *= b;
            n >>= 1;
            b *= b;
        }
        return x;
    }
    friend ModInt operator+(ModInt lhs, const ModInt &rhs) { return lhs += rhs; }
    friend ModInt operator-(ModInt lhs, const ModInt &rhs) { return lhs -= rhs; }
    friend ModInt operator*(ModInt lhs, const ModInt &rhs) { return lhs *= rhs; }
    friend ModInt operator/(ModInt lhs, const ModInt &rhs) { return lhs /= rhs; }
    ModInt &operator+=(const ModInt &x) {
        if ((val += x.val) >= MOD)
            val -= MOD;
        return *this;
    }
    ModInt &operator-=(const ModInt &x) {
        if ((val -= x.val) < 0)
            val += MOD;
        return *this;
    }
    ModInt &operator*=(const ModInt &x) {
        val = prod_type(val) * x.val % MOD;
        return *this;
    }
    ModInt &operator/=(const ModInt &x) { return *this *= x.inv(); }
    bool operator==(const ModInt &b) const { return val == b.val; }
    bool operator!=(const ModInt &b) const { return val != b.val; }
    friend std::istream &operator>>(std::istream &is, ModInt &x) noexcept {
        return is >> x.val;
    }
    friend std::ostream &operator<<(std::ostream &os, const ModInt &x) noexcept {
        return os << x.val;
    }
};
using ModInt1000000007 = ModInt<int, 1'000'000'007>;
using ModInt998244353 = ModInt<int, 998244353>;
