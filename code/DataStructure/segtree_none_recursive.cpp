struct SegTree{
    int n;
    vector<int> t;
    SegTree(int n_):n(n_),t(2*n){}
    SegTree(vector<int>& a):SegTree((int)a.size()){
        for (int i=0;i<n;i++) t[n+i]=a[i];
        for (int i = n - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
    }

    void update(int p, int value) {  // set value at position p
        t[p += n] = value;
        for (; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
    }

    int query(int l, int r) {  // sum on interval [l, r)
        int res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) res += t[l++];
            if (r&1) res += t[--r];
        }
        return res;
    }
};
