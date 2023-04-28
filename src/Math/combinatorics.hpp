#pragma once
#include <vector>

template <typename mint>
struct Combi {
    std::vector<mint> fac, invfac;
    constexpr Combi(const int n) : fac(n + 1), invfac(n + 1) {
        fac[0] = 1;
        for (int i = 1; i <= n; i++) {
            fac[i] = fac[i - 1] * i;
        }
        invfac[n] = fac[n].inv();
        for (int i = n - 1; i >= 0; i--) {
            invfac[i] = invfac[i + 1] * (i + 1);
        }
    }
    mint operator[](int k) const {
        assert(k < (int)size(fac));
        return fac[k];
    }
    mint operator()(int n, int k) const {
        return C(n, k);
    }
    mint C(int n, int k) const { // n choose m
        if (k < 0 || k > n) return 0;
        assert((int)size(fac) > n);
        return fac[n] * invfac[n - k] * invfac[k];
    }
    mint P(int n, int k) { // n choose m with permutation
        if (k < 0 || k > n) return 0;
        assert((int)size(fac) > n);
        return fac[n] * invfac[n - k];
    }
    mint catalan(int n) {
        assert(2 * n < (int)size(fac));
        return C(2 * n, n) - C(2 * n, n - 1);
    }

    // evaluate expressions consisting of multiplication and division
    // if the number is multiplied, pass the number as argument
    // if divided, pass its negation
    // Example: a! * b! / c! => eval(a, b, -c);
    template<typename... Args>
    constexpr mint eval(Args... args) {
        return ((args > 0 ? fac[args] : invfac[-args]) * ...);
    }
};
