#pragma once
#include <vector>
#include "misc/util.hpp"
template <typename T> struct Fenwick {
    int n;
    std::vector<T> t;

    Fenwick(int n_) : n(n_), t(n + 1) {}
    Fenwick(const std::vector<T> &v) : Fenwick((int)v.size()) {
        for (int i = 1; i <= n; i++) {
            t[i] += v[i - 1];
            int j = i + (i & -i);
            if (j <= n) t[j] += t[i];
        }
    }

    void add(int i, const T& x) {
        assert(i >= 0 && i < n);
        for (i++; i <= n; i += i & -i) {
            t[i] += x;
        }
    }

    // Returns `data[0] + ... + data[i - 1]`.
    template <typename U = T> U get(int i) {
        assert(i >= 0 && i <= n);
        U res{};
        for (; i > 0; i -= i & -i)
            res += t[i];
        return res;
    }

    // Returns `data[l] + ... + data[r - 1]`.
    template <typename U = T> U get(int l, int r) {
        assert(l >= 0);
        assert(l <= r);
        assert(r <= n);
        return get<U>(r) - get<U>(l);
    }

    // Returns the position of the first element in the prefix sum array
    // that doesn't satisfy predicate p
    template<class UnaryPredicate>
    int partition_point(UnaryPredicate p) {
        int pos = 0;
        T sum{};
        for (int i = lg(n); i >= 0; i--) {
            int next = pos + (1 << i);
            if (next <= n && p(sum + t[next])) {
                sum += t[next];
                pos = next;
            }
        }
        return pos;
    }

    // Returns the position of the first element in the prefix sum array
    // that is greater than or equal to target
    int lower_bound(const T& target) {
        return partition_point([&](auto x) { return x < target; });
    }

    // Returns the position of the first element in the prefix sum array
    // that is greater than target
    int upper_bound(const T& target) {
        return partition_point([&](auto x) { return x <= target; });
    }
};
// fenwick tree with range update and range sum query
struct fenwick_rg {
    int n;
    std::vector<int64_t> sum1, sum2;
    fenwick_rg(int n_) : n(n_), sum1(n + 1), sum2(n + 1) {}

  private:
    void add(int i, int x) {
        assert(i >= 0 && i < n);
        i++;
        int64_t v = (int64_t)i * x;
        for (; i <= n; i += i & -i)
            sum1[i] += x, sum2[i] += v;
    }

  public:
    void add(int l, int r, int x) {
        assert(l >= 0 && l <= r && r < n);
        add(l, x);
        if (r + 1 < n) add(r + 1, -x);
    }
    int64_t query(int p) {
        assert(p >= 0 && p < n);
        p++;
        int64_t res{};
        for (int i = p; i; i -= i & -i)
            res += (p + 1) * sum1[i] - sum2[i];
        return res;
    }
    int64_t query(int l, int r) {
        assert(l >= 0 && l <= r && r < n);
        return query(r) - (l ? query(l - 1) : 0);
    }
};
