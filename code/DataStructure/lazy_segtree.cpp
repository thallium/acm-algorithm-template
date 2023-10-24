// segment tree with lazy propagation
#include<bits/stdc++.h>
using namespace std;

struct lazyseg {
    using s = int;
    using f = int;

    s e() {}
    s op(const s& x, const s& y) {}
    f id() {}
    f comp(const f& neo, const f& old) {}
    s mp(f, s) {}

    int n;
    vector<s> d;
    vector<f> lz;
    explicit lazyseg(int n) : lazyseg(vector<s>(n, e())) {}
    lazyseg(const vector<s> &v) : n((int)size(v)), d(4 * n), lz(4 * n, id()) {
        build(1, 0, n - 1, v);
    }
    void pull(int k) { d[k] = op(d[k * 2], d[k * 2 + 1]); }
    void build(int k, int l, int r, const vector<s>& v) {
        if (l == r) {
            d[k] = v[l];
            return;
        }
        int mid = (l + r) / 2;
        build(k * 2, l, mid, v);
        build(k * 2 + 1, mid + 1, r, v);
        pull(k);
    }
    void all_apply(int k, f f) {
        d[k] = mp(f, d[k]);
        lz[k] = comp(f, lz[k]);
    }
    void push(int k) {
        all_apply(k * 2, lz[k]);
        all_apply(k * 2 + 1, lz[k]);
        lz[k] = id();
    }
    void apply(int k, int ql, int qr, int l, int r, f x) {
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
    s get(int k, int ql, int qr, int l, int r) {
        if (qr < l || ql > r) return e();
        if (ql <= l && qr >= r) return d[k];
        push(k);
        int mid = (l + r) / 2;
        return op(get(k * 2, ql, qr, l, mid), get(k * 2 + 1, ql, qr, mid + 1, r));
    }
    void apply(int l, int r, f x) {
        if (r < l) return;
        assert(l >= 0 && l <= r && r < n);
        apply(1, l, r, 0, n - 1, x);
    }
    s get(int i) {
        assert(i >= 0 && i < n);
        return get(1, i, i, 0, n - 1);
    }
    s get(int l, int r) {
        assert(l >= 0 && l <= r && r < n);
        return get(1, l, r, 0, n - 1);
    }
    template<class G> int max_right(int ql, G f) {
        assert(0 <= ql && ql <= n);
        assert(f(e()));
        s sum = e();
        auto rec = [&](auto& slf, int k, int l, int r) {
            if (s s = op(sum, d[k]); l >= ql && f(s)) {
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
        s sum = e();
        auto rec = [&](auto& slf, int k, int l, int r) {
            if (s s = op(d[k], sum); r <= qr && f(s)) {
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
