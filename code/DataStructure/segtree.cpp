#include <vector>
using namespace std;

template<class s, auto op, auto e>
struct segtree {
    int n;
    vector<s> d;
    segtree(int n) : n(n), d(4 * n) {
        build(1, 0, n - 1, vector<s>(n, e()));
    }
    segtree(const vector<s> &v) : n((int)v.size()), d(4 * n) {
        build(1, 0, n - 1, v);
    }
    void pull(int k) { d[k] = op(d[k * 2], d[k * 2 + 1]); }
    void build(int p, int l, int r, const vector<s> &v) {
        if (l == r) {
            d[p] = v[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(p * 2, l, mid, v);
        build(p * 2 + 1, mid + 1, r, v);
        pull(p);
    }
    void set(int p, int i, s x, int l, int r) {
        if (l == r) {
            d[p] = x;
            return;
        }
        int m = (l + r) / 2;
        if (i <= m) set(p * 2, i, x, l, m);
        else set(p * 2 + 1, i, x, m + 1, r);
        pull(p);
    }
    s get(int p, int ql, int qr, int l, int r) {
        if (ql > r || qr < l) return e();
        if (ql <= l && qr >= r) return d[p];
        int m = (l + r) / 2;
        return op(get(p * 2, ql, qr, l, m), get(p * 2 + 1, ql, qr, m + 1, r));
    }
    s get(int i) {
        assert(i >= 0 && i < n);
        return get(1, i, i, 0, n - 1);
    }
    s get(int l, int r) {
        assert(l >= 0 && l <= r && r < n);
        return get(1, l, r, 0, n - 1);
    }
    void set(int i, s x) {
        assert(i >= 0 && i < n);
        set(1, i, x, 0, n - 1);
    }
    // return the largest r such that f(op(d[ql], ..., d[r])) is true
    template<class G> int max_right(int ql, G f) {
        assert(0 <= ql && ql <= n);
        assert(f(e()));
        s sum = e();
        auto rec = [&](auto& slf, int k, int l, int r) {
            if (l >= ql) {
                auto ss = op(sum, d[k]);
                if (f(ss)) {
                    sum = op(sum, d[k]);
                    return r;
                }
            }
            if (l == r) return l - 1;
            int mid = (l + r) / 2;
            if (ql <= mid) {
                int res = slf(slf, k * 2, l, mid);
                if (res != mid) return res;
            }
            return slf(slf, k * 2 + 1, mid + 1, r);
        };
        return rec(rec, 1, 0, n - 1);
    }

    // return the smallest l such that f(op(d[l], ..., d[qr])) is true
    template<class G> int min_left(int qr, G f) {
        assert(-1 <= qr && qr < n);
        assert(f(e()));
        if (qr == -1) return 0;
        s sum = e();
        auto rec = [&](auto& slf, int k, int l, int r) {
            if (r <= qr) {
                s ss = op(d[k], sum);
                if (f(ss)) {
                    sum = op(d[k], sum);
                    return l;
                }
            }
            if (l == r) return l + 1;
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
