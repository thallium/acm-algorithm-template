#pragma once
#include <vector>

// fenwick tree with range update and range sum query
class fenwick_rg {
    int n;
    std::vector<int64_t> sum1, sum2;

    void add(int i, int x) {
        assert(i >= 0 && i < n);
        i++;
        int64_t v = (int64_t)i * x;
        for (; i <= n; i += i & -i)
            sum1[i] += x, sum2[i] += v;
    }

public:
    fenwick_rg(int n_) : n(n_), sum1(n + 1), sum2(n + 1) {}
    // [l, r)
    void add(int l, int r, int x) {
        assert(l >= 0 && l < r && r <= n);
        add(l, x);
        if (r < n)
            add(r, -x);
    }
    int64_t get(int p) {
        assert(p >= 0 && p <= n);
        int64_t res{};
        for (int i = p; i; i -= i & -i)
            res += (p + 1) * sum1[i] - sum2[i];
        return res;
    }

    // [l, r)
    int64_t get(int l, int r) {
        assert(l >= 0 && l < r && r <= n);
        return get(r) - get(l);
    }
};
