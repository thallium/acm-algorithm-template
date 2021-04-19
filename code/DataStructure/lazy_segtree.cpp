// lazy propagation
struct SegTree {
    // remember to change the type and pushup function
    int n;
    vector<int> t, lazy;
    SegTree(int n_) : n(n_), t(4 * n), lazy(4 * n) {}
    SegTree(const vector<int> &v) : SegTree((int)v.size()) {
        build(1, 0, n - 1, v);
    }
    void pull(int node) { t[node] = t[node * 2] + t[node * 2 + 1]; }
    void build(int node, int l, int r, const vector<int> &v) {
        if (l == r) {
            t[node] = v[l];
            return;
        }
        int mid = (l + r) / 2;
        build(node * 2, l, mid, v);
        build(node * 2 + 1, mid + 1, r, v);
        pull(node);
    }

    void addtag(int p, int x, int l, int r) {
        t[p] += (r - l + 1) * x;
        lazy[p] += x;
    }

    void push(int p, int l, int r) {
        if (lazy[p]) {
            int m = (l + r) / 2;
            addtag(p * 2, lazy[p], l, m);
            addtag(p * 2 + 1, lazy[p], m + 1, r);
            lazy[p] = 0;
        }
    }

    void update(int node, int ql, int qr, int l, int r, int x) {
        if (r < ql || l > qr) return;
        if (ql <= l && qr >= r) return addtag(node, x, l, r);
        push(node, l, r);
        int mid = (l + r) / 2;
        update(node * 2, ql, qr, l, mid, x);
        update(node * 2 + 1, ql, qr, mid + 1, r, x);
        pull(node);
    }

    ll query(int node, int ql, int qr, int l, int r) {
        if (r < ql || l > qr) return 0;
        if (ql <= l && qr >= r) return t[node];
        push(node, l, r);
        int mid = (l + r) / 2;
        return query(node * 2, ql, qr, l, mid) +
            query(node * 2 + 1, ql, qr, mid + 1, r);
    }
};
