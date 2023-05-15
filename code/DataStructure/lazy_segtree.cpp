// segment tree with lazy propagation
#include<bits/stdc++.h>
using namespace std;

struct LazySegTree {
    struct S {

    };
    struct F {

    };

    S e() {}
    S op(const S& x, const S& y) {}
    F id() {}
    F comp(const F& neo, const F& old) {}
    S mp(F, S) {}

    int n;
    vector<S> d;
    vector<F> lz;
    explicit LazySegTree(int n) : LazySegTree(vector<S>(n, e())) {}
    LazySegTree(const vector<S> &v) : n((int)size(v)), d(4 * n), lz(4 * n) {
        build(1, 0, n - 1, v);
    }
    void pull(int k) { d[k] = op(d[k * 2], d[k * 2 + 1]); }
    void build(int k, int l, int r, const vector<S>& v) {
        if (l == r) {
            d[k] = v[l];
            return;
        }
        int mid = (l + r) / 2;
        build(k * 2, l, mid, v);
        build(k * 2 + 1, mid + 1, r, v);
        pull(k);
    }
    void all_apply(int k, F f) {
        d[k] = mp(f, d[k]);
        lz[k] = comp(f, lz[k]);
    }
    void push(int k) {
        all_apply(k * 2, lz[k]);
        all_apply(k * 2 + 1, lz[k]);
        lz[k] = id();
    }
    void apply(int k, int ql, int qr, int l, int r, F x) {
        if (r < ql || l > qr) return;
        if (ql <= l && qr >= r) {
            return all_apply(k, x);
        }
        push(k);
        int mid = (l + r) / 2;
        apply(k * 2, ql, qr, l, mid, x);
        apply(k * 2 + 1, ql, qr, mid + 1, r, x);
        pull(k);
    }
    S get(int k, int ql, int qr, int l, int r) {
        if (qr < l || ql > r) return e();
        if (ql <= l && qr >= r) return d[k];
        push(k);
        int mid = (l + r) / 2;
        return op(get(k * 2, ql, qr, l, mid), get(k * 2 + 1, ql, qr, mid + 1, r));
    }
    void apply(int l, int r, F x) {
        if (r < l) return;
        assert(l >= 0 && l <= r && r < n);
        apply(1, l, r, 0, n - 1, x);
    }
    S get(int p) {
        assert(p >= 0 && p < n);
        return get(1, p, p, 0, n - 1);
    }
    S get(int l, int r) {
        assert(l >= 0 && l <= r && r < n);
        return get(1, l, r, 0, n - 1);
    }
    template<class G> int max_right(int ql, G f) {
        assert(0 <= ql && ql <= n);
        assert(f(e()));
        S sum = e();
        auto rec = [&](auto& slf, int k, int l, int r) {
            if (S s = op(sum, d[k]); l >= ql && f(s)) {
                sum = s;
                return r;
            }
            if (l == r) return l - 1;
            push(k);
            int mid = (l + r) / 2;
            if (ql <= mid) {
                int res = slf(slf, k * 2, l, mid);
                if (res != mid) return res;
            }
            return slf(slf, k * 2 + 1, mid + 1, r);
        };
        return rec(rec, 1, 0, n - 1);
    }
    template<class G> int min_left(int qr, G f) {
        assert(-1 <= qr && qr < n);
        assert(f(e()));
        S sum = e();
        auto rec = [&](auto& slf, int k, int l, int r) {
            if (S s = op(d[k], sum); r <= qr && f(s)) {
                sum = s;
                return l;
            }
            if (l == r) return l + 1;
            push(k);
            int mid = (l + r) / 2;
            if (qr > mid) {
                int res = slf(slf, k * 2 + 1, mid + 1, r);
                if (res != mid + 1) return res;
            }
            return slf(slf, k * 2, l, mid);
        };
        return rec(rec, 1, 0, n - 1);
    }
};
