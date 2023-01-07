#pragma once

#include <algorithm>
#include <vector>

#include "misc/util.hpp"

// template <class typename T::S, typename T::S (*op)(typename T::S, typename T::S), typename T::S (*e)()> struct segtree {
template <typename T> struct segtree {
  public:
    segtree() : segtree(0) {}
    explicit segtree(int n) : segtree(std::vector<typename T::S>(n, T::e())) {}
    explicit segtree(const std::vector<typename T::S>& v) : _n(int(v.size())) {
        log = ceil_lg(_n);
        size = 1 << log;
        d = std::vector<typename T::S>(2 * size, T::e());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, typename T::S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    typename T::S get(int p) const {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    typename T::S prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        typename T::S sml = T::e(), smr = T::e();
        l += size;
        r += size;

        while (l < r) {
            if (l & 1) sml = T::op(sml, d[l++]);
            if (r & 1) smr = T::op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return T::op(sml, smr);
    }

    typename T::S all_prod() const { return d[1]; }

    template <bool (*f)(typename T::S)> int max_right(int l) const {
        return max_right(l, [](typename T::S x) { return f(x); });
    }
    template <class F> int max_right(int l, F f) const {
        assert(0 <= l && l <= _n);
        assert(f(T::e()));
        if (l == _n) return _n;
        l += size;
        typename T::S sm = T::e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(T::op(sm, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(T::op(sm, d[l]))) {
                        sm = T::op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = T::op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*f)(typename T::S)> int min_left(int r) const {
        return min_left(r, [](typename T::S x) { return f(x); });
    }
    template <class F> int min_left(int r, F f) const {
        assert(0 <= r && r <= _n);
        assert(f(T::e()));
        if (r == 0) return 0;
        r += size;
        typename T::S sm = T::e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(T::op(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(T::op(d[r], sm))) {
                        sm = T::op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = T::op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, size, log;
    std::vector<typename T::S> d;

    void update(int k) { d[k] = T::op(d[2 * k], d[2 * k + 1]); }
};
