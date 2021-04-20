#include <bits/stdc++.h>
using namespace std;
template <typename T>
struct SegTree {
    int n;
    vector<T> t;

    SegTree(int n_) : n(n_), t(4 * n) {
        build(1, 0, n-1, vector(n, T()));
    }

    template<typename U>
    SegTree(const vector<T> &v) : SegTree((int)v.size()) {
        build(1, 0, n - 1, v);
    }

    void pull(int node) { t[node] = t[node << 1] + t[node << 1 | 1]; }

    template<typename U>
    void build(int node, int l, int r, const vector<U> &v) {
        if (l == r) {
            t[node] = T(v[l]);
            return;
        }
        int mid = (l + r) >> 1;
        build(node << 1, l, mid, v);
        build(node << 1 | 1, mid + 1, r, v);
        pull(node);
    }

    template<typename U>
    void add(int node, int i, U x, int l, int r) {
        if (l == r) {
            t[node] += x;
            return;
        }
        int mid = (l + r) / 2;
        if (i <= mid) update(node << 1, i, x, l, mid);
        else update(node << 1 | 1, i, x, mid + 1, r);
        pull(node);
    }

    void set(int node, int i, T x, int l, int r) {
        if (l == r) {
            t[node] = x;
            return;
        }
        int mid = (l + r) / 2;
        if (i <= mid) update(node << 1, i, x, l, mid);
        else update(node << 1 | 1, i, x, mid + 1, r);
        pull(node);
    }

    T get(int node, int ql, int qr, int l, int r) {
        if (ql <= l && qr >= r) return t[node];

        int mid = (l + r) >> 1;
        if (qr <= mid) return get(node << 1, ql, qr, l, mid);
        if (ql > mid) return get(node << 1 | 1, ql, qr, mid+1, r);
        return get(node << 1, ql, qr, l, mid) + get(node << 1 | 1, ql, qr, mid+1, r);
    }
    // wrapper
    template <typename U>
    void add(int i, U x) {
        add(1, i, x, 0, n-1);
    }

    void set(int i, T x) {
        set(1, i, x, 0, n-1);
    }

    T get(int l, int r) {
        return get(1, l, r, 0, n-1);
    }
};

struct node {
    int v=0; // value for leaves

    node() = default;
    // may need more constructor

    node operator+(const node& rhs) const {
        return {v+rhs.v};
    }

    node& operator +=(const node& rhs) {
        v+=rhs.v;
        return *this;
    }
};
