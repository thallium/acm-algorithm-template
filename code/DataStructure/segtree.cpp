#include <vector>
using namespace std;

template <class S, auto op, auto e> struct SegTree {
    int n;
    vector<S> d;
    explicit SegTree(int n) : n(n), d(4 * n) {
        build(1, 0, n - 1, vector<S>(n, e()));
    }
    SegTree(const vector<S> &v) : SegTree((int)v.size()) {
        build(1, 0, n - 1, v);
    }
    void pull(int k) { d[k] = d[k * 2] + d[k * 2 + 1]; }
    void build(int p, int l, int r, const vector<S> &v) {
        if (l == r) {
            d[p] = v[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(p * 2, l, mid, v);
        build(p * 2 + 1, mid + 1, r, v);
        pull(p);
    }
    void set(int p, int i, S x, int l, int r) {
        if (l == r) {
            d[p] = x;
            return;
        }
        int m = (l + r) / 2;
        if (i <= m) set(p * 2, i, x, l, m);
        else set(p * 2 + 1, i, x, m + 1, r);
        pull(p);
    }
    S get(int p, int ql, int qr, int l, int r) {
        if (ql > r || qr < l) return e();
        if (ql <= l && qr >= r) return d[p];
        int m = (l + r) / 2;
        return op(get(p * 2, ql, qr, l, m), get(p * 2 + 1, ql, qr, m + 1, r));
    }
    S get(int i) {
        assert(i >= 0 && i < n);
        return get(1, i, i, 0, n - 1);
    }
    S get(int l, int r) {
        assert(l >= 0 && l <= r && r < n);
        return get(1, l, r, 0, n - 1);
    }
    void set(int i, S x) {
        assert(i >= 0 && i < n);
        set(1, i, x, 0, n - 1);
    }
    // return the largest r such that f(op(d[ql], ..., d[r])) is true
    template<class G> int max_right(int ql, G f) {
        assert(0 <= ql && ql <= n);
        assert(f(e()));
        S sum = e();
        auto rec = [&](auto& slf, int k, int l, int r) {
            if (l >= ql && f(op(sum, d[k]))) {
                sum = op(sum, d[k]);
                return r;
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
    template<class G> int min_left(int qr, G f) {
        assert(-1 <= qr && qr < n);
        assert(f(e()));
        S sum = e();
        auto rec = [&](auto& slf, int k, int l, int r) {
            if (r <= qr && f(op(d[k], sum))) {
                sum = op(d[k], sum);
                return l;
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
