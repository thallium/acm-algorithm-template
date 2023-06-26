#pragma once
#include <vector>
#include <functional>
#include "misc/util.hpp"

template <typename T> struct SparseTable {
    size_t n, logn;
    std::vector<std::vector<T>> v;
    std::function<T(T, T)> F;

    SparseTable() = default;
    template<typename Func>
    SparseTable(const std::vector<T> &a, Func f)
        : n(a.size()), logn(lg(n)), v(logn + 1, std::vector<T>(n)), F(f) {
        v[0] = a;
        for (size_t i = 1; i <= logn; i++)
            for (size_t j = 0; j + (1 << i) - 1 < n; j++)
                v[i][j] = F(v[i - 1][j], v[i - 1][j + (1 << (i - 1))]);
    }

    // [l, r)
    T query(size_t l, size_t r) {
        assert(l < r);
        assert(l < n);
        assert(r <= n);
        int s = lg(r - l);
        return F(v[s][l], v[s][r - (1 << s)]);
    }
};
