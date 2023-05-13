#pragma once
// Lagrange Interpolation

#include <vector>
#include "math/combinatorics.hpp"

// Evaluate Lagrange polynomial interpolating consecutive x values at x_eval in O(n) time
// Tested on https://codeforces.com/contest/622/problem/F
template <typename T, typename U>
static T linear_lagrange_interpolation(int x_start, const std::vector<U>& y, int x_eval) {
    T ans{};
    const int n = (int)size(y);
    static Combi<T> c(n);

    std::vector<T> pre(n + 1), suf(n + 1);
    pre[0] = suf[n] = 1;
    for (int i = 0; i < n; i++) {
        pre[i + 1] = pre[i] * (x_eval - (x_start + i));
    }
    for (int i = n - 1; i >= 0; i--) {
        suf[i] = suf[i + 1] * (x_eval - (x_start + i));
    }

    for (int i = 0; i < n; i++) {
        auto numerator = pre[i] * suf[i + 1];
        auto denominator = T((n - i) % 2 ? 1 : -1) * c.invfac[i] * c.invfac[n - 1 - i];
        ans += numerator * denominator * y[i];
    }

    return ans;
}

// Regular Lagrange Interpolation
// Tested on: https://www.luogu.com.cn/problem/P4781
template <typename T, typename U>
static T lagrange_interpolation(const std::vector<U>& x, const std::vector<U>& y, int x_eval) {
    T ans{};
    const int n = (int)size(x);

    for (int i = 0; i < n; i++) {
        T numerator = y[i];
        T denominator = 1;
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            numerator *= (x_eval - x[j]);
            denominator *= (x[i] - x[j]);
        }
        ans += numerator / denominator;
    }

    return ans;
}
