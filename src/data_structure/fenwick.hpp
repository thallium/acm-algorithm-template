#pragma once
#include <vector>
#include "misc/util.hpp"
template <typename T> struct Fenwick {
    std::size_t n;
    std::vector<T> t;

    Fenwick(std::size_t n_) : n(n_), t(n + 1) {}
    Fenwick(const std::vector<T> &v) : Fenwick(v.size()) {
        for (std::size_t i = 1; i <= n; i++) {
            t[i] += v[i - 1];
            std::size_t j = i + (i & -i);
            if (j <= n) t[j] += t[i];
        }
    }

    void add(std::size_t i, const T& x) {
        assert(i >= 0 && i < n);
        for (i++; i <= n; i += i & -i) {
            t[i] += x;
        }
    }

    // Returns `data[0] + ... + data[i - 1]`.
    template <typename U = T> U get(std::size_t i) {
        assert(i >= 0 && i <= n);
        U res{};
        for (; i > 0; i -= i & -i)
            res += t[i];
        return res;
    }

    // Returns `data[l] + ... + data[r - 1]`.
    template <typename U = T> U get(std::size_t l, std::size_t r) {
        assert(l >= 0);
        assert(l <= r);
        assert(r <= n);
        return get<U>(r) - get<U>(l);
    }

    // Returns the position of the first element in the prefix sum array
    // that doesn't satisfy predicate p
    template<class UnaryPredicate>
    std::size_t partition_point(UnaryPredicate p) {
        std::size_t pos = 0;
        T sum{};
        for (std::size_t i = lg(n); i >= 0; i--) {
            std::size_t next = pos + (1 << i);
            if (next <= n && p(sum + t[next])) {
                sum += t[next];
                pos = next;
            }
        }
        return pos;
    }

    // Returns the position of the first element in the prefix sum array
    // that is greater than or equal to target
    std::size_t lower_bound(const T& target) {
        return partition_point([&](auto x) { return x < target; });
    }

    // Returns the position of the first element in the prefix sum array
    // that is greater than target
    std::size_t upper_bound(const T& target) {
        return partition_point([&](auto x) { return x <= target; });
    }
};
