// lazy propagation
#include<bits/stdc++.h>
using namespace std;
struct SegTree {
    struct node {
        int v=0; // don't forget to set default value (used for leaves), not necessarily zero element
        int lazy=0;

        void apply(int l, int r, int x) {
            lazy += x;
            v += (r - l + 1) * x;
        }

        bool has_lazy() { // used to check if need to propagate
            return lazy!=0;
        }

        void clear_lazy() {
            lazy=0;
        }

        node merge(const node& b) const {
            node res;
            res.v=v+b.v;
            return res;
        }
    };
    int n;
    vector<node> t;
    SegTree(int n_) : n(n_), t(4 * n) {}
    SegTree(int n_, int x) : SegTree(n_) {
        build(1, 0, n - 1, [&](int i) { return x; });
    }
    SegTree(int n_, function<int(int)> f) : SegTree(n_) {
        build(1, 0, n-1, f);
    }
    SegTree(const vector<int> &v) : SegTree((int)v.size()) {
        build(1, 0, n - 1, [&](int i) { return v[i]; });
    }
    void pull(int node) { t[node] = t[node * 2].merge(t[node * 2 + 1]); }
    void build(int node, int l, int r, function<int(int)> f) {
        if (l == r) {
            return t[node].apply(l, r, f(l));
        }
        int mid = (l + r) / 2;
        build(node * 2, l, mid, f);
        build(node * 2 + 1, mid + 1, r, f);
        pull(node);
    }
    void push(int p, int l, int r) {
        if (t[p].has_lazy()) {
            int m = (l + r) / 2;
            t[p * 2].apply(l, m, t[p].lazy);
            t[p * 2 + 1].apply(m + 1, r, t[p].lazy);
            t[p].clear_lazy();
        }
    }
    template<typename U>
    void update(int node, int ql, int qr, int l, int r, U x) {
        if (r < ql || l > qr) return;
        if (ql <= l && qr >= r) return t[node].apply(l, r, x);
        push(node, l, r);
        int mid = (l + r) / 2;
        update(node * 2, ql, qr, l, mid, x);
        update(node * 2 + 1, ql, qr, mid + 1, r, x);
        pull(node);
    }
    node get(int node, int ql, int qr, int l, int r) {
        if (ql <= l && qr >= r) return t[node];
        push(node, l, r);
        int mid = (l + r) / 2;
        if (qr <= mid) return get(node << 1, ql, qr, l, mid);
        if (ql > mid) return get(node << 1 | 1, ql, qr, mid+1, r);
        return get(node << 1, ql, qr, l, mid).merge(get(node << 1 | 1, ql, qr, mid+1, r));
    }
    // wrapper
    template <typename U>
    void add(int l, int r, U x) {
        assert(l >= 0 && l <= r && r < n);
        update(1, l, r, 0, n-1, x);
    }
    node get(int l, int r) {
        assert(l >= 0 && l <= r && r < n);
        return get(1, l, r, 0, n-1);
    }
};
