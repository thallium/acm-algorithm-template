template <int MOD>
struct ModInt {
    int val;
    ModInt(int v = 0) : val(v % MOD) { if (val < 0) val += MOD; };
    ModInt operator+() const { return ModInt(val); }
    ModInt operator-() const { return ModInt(MOD - val); }
    ModInt inv() const {
        auto a = val, m = MOD, u = 0, v = 1;
        while (a != 0) { auto t = m / a; m -= t * a; swap(a, m); u -= t * v; swap(u, v); }
        assert(m == 1);
        return u;
    }
    friend ModInt operator+ (ModInt lhs, const ModInt& rhs) { return lhs += rhs; }
    friend ModInt operator- (ModInt lhs, const ModInt& rhs) { return lhs -= rhs; }
    friend ModInt operator* (ModInt lhs, const ModInt& rhs) { return lhs *= rhs; }
    friend ModInt operator/ (ModInt lhs, const ModInt& rhs) { return lhs /= rhs; }
    ModInt& operator+=(const ModInt& x) { if ((val += x.val) >= MOD) val -= MOD; return *this; }
    ModInt& operator-=(const ModInt& x) { if ((val -= x.val) < 0) val += MOD; return *this; }
    ModInt& operator*=(const ModInt& x) { val = int64_t(val) * x.val % MOD; return *this; }
    ModInt& operator/=(const ModInt& x) { return *this *= x.inv(); }
    bool operator==(const ModInt& b) const { return val == b.val; }
    bool operator!=(const ModInt& b) const { return val != b.val; }
    friend std::istream& operator>>(std::istream& is, ModInt& x) noexcept { return is >> x.val; }
    friend std::ostream& operator<<(std::ostream& os, const ModInt& x) noexcept { return os << x.val; }
};
using mint = ModInt<1'000'000'007>;
