#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include "misc/util.hpp"

template <typename T>
struct lazy_segtree {
  public:
    lazy_segtree() : lazy_segtree(0) {}
    explicit lazy_segtree(int n) : lazy_segtree(std::vector<typename T::S>(n, T::e())) {}
    explicit lazy_segtree(const std::vector<typename T::S>& v) : _n(int(v.size())) {
        log = (int)ceil_lg((std::size_t)_n);
        size = 1 << log;
        d = std::vector<typename T::S>(2 * size, T::e());
        lz = std::vector<typename T::F>(size, T::id());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, typename T::S x) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    typename T::S get(int p) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }

    typename T::S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return T::e();

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        typename T::S sml = T::e(), smr = T::e();
        while (l < r) {
            if (l & 1) sml = T::op(sml, d[l++]);
            if (r & 1) smr = T::op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }

        return T::op(sml, smr);
    }

    typename T::S all_prod() { return d[1]; }

    void apply(int p, typename T::F f) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = T::mapping(f, d[p]);
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    void apply(int l, int r, typename T::F f) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return;

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }

        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    template <bool (*g)(typename T::S)> int max_right(int l) {
        return max_right(l, [](typename T::S x) { return g(x); });
    }
    template <class G> int max_right(int l, G g) {
        assert(0 <= l && l <= _n);
        assert(g(T::e()));
        if (l == _n) return _n;
        l += size;
        for (int i = log; i >= 1; i--) push(l >> i);
        typename T::S sm = T::e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(T::op(sm, d[l]))) {
                while (l < size) {
                    push(l);
                    l = (2 * l);
                    if (g(T::op(sm, d[l]))) {
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

    template <bool (*g)(typename T::S)> int min_left(int r) {
        return min_left(r, [](typename T::S x) { return g(x); });
    }
    template <class G> int min_left(int r, G g) {
        assert(0 <= r && r <= _n);
        assert(g(T::e()));
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        typename T::S sm = T::e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(T::op(d[r], sm))) {
                while (r < size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(T::op(d[r], sm))) {
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
    std::vector<typename T::F> lz;

    void update(int k) { d[k] = T::op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, typename T::F f) {
        d[k] = T::mapping(f, d[k]);
        if (k < size) lz[k] = T::composition(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = T::id();
    }
};
