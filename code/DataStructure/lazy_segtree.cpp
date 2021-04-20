#include <bits/stdc++.h>
using namespace std;
// lazy propagation
template<typename T>
struct SegTree {
    int n;
    vector<T> t;
    SegTree(int n_) : n(n_), t(4 * n) {}
    template<typename U>
    SegTree(const vector<U> &v) : SegTree((int)v.size()) {
        build(1, 0, n - 1, v);
    }
    void pull(int node) { t[node] = t[node * 2] + t[node * 2 + 1]; }
    template<typename U>
    void build(int node, int l, int r, const vector<U> &v) {
        if (l == r) {
            return t[node].apply(l, r, v[l]);
        }
        int mid = (l + r) / 2;
        build(node * 2, l, mid, v);
        build(node * 2 + 1, mid + 1, r, v);
        pull(node);
    }

    void push(int p, int l, int r) {
        if (t[p].lazy) {
            int m = (l + r) / 2;
            t[p * 2].apply(t[p].lazy, l, m);
            t[p * 2 + 1].apply(t[p].lazy, m + 1, r);
            t[p].lazy = 0;
        }
    }

    template<typename U>
    void add(int node, int ql, int qr, int l, int r, U x) {
        if (r < ql || l > qr) return;
        if (ql <= l && qr >= r) return t[node].apply(x, l, r);
        push(node, l, r);
        int mid = (l + r) / 2;
        add(node * 2, ql, qr, l, mid, x);
        add(node * 2 + 1, ql, qr, mid + 1, r, x);
        pull(node);
    }

    T get(int node, int ql, int qr, int l, int r) {
        if (ql <= l && qr >= r) return t[node];
        push(node, l, r);
        int mid = (l + r) / 2;

        if (qr <= mid) return get(node << 1, ql, qr, l, mid);
        if (ql > mid) return get(node << 1 | 1, ql, qr, mid+1, r);
        return get(node << 1, ql, qr, l, mid) + get(node << 1 | 1, ql, qr, mid+1, r);
    }
};

struct node {
    int v=0; // don't forget to set default value (used for leaves), not necessarily zero element
    int lazy=0;
    void apply(int l, int r, int x) {
        v+=x;
        lazy+=(r-l) * x;
    }

    node operator+(const node& b) const {
        node res;
        res.v=v+b.v;
        return res;
    }
};
