#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template <typename T> struct fenwick {
    int n; vector<T> t;
    fenwick(int n) : n(n), t(n + 1) {}
    void add(int i, T x) {
        assert(i >= 0 && i < n);
        for (i++; i <= n; i += i & -i) {
            t[i] += x;
        }
    }
    // change return type if needed
    T query(int i) {
        assert(i >= -1 && i < n);
        T res{};
        for (i++; i > 0; i -= i & -i)
            res += t[i];
        return res;
    }
    // change return type if needed
    T query(int l, int r) {
        assert(l >= 0 && l <= r && r < n);
        return query(r) - query(l - 1);
    }
    int search(T prefix) { // finds first pos s.t. sum(0, pos)>=prefix
        int pos = 0;
        T sum = 0;
        for (int i = __lg(n); i >= 0; i--) {
            // could change < to <= to make it find upper bound
            if (int nxt = pos + (1 << i); nxt <= n && (sum + t[nxt] < prefix)) {
                pos = nxt;
                sum += t[pos];
            }
        }
        return pos;
    }
};

// fenwick tree with range update and range sum query
struct fenwick_rg {
    int n;
    vector<ll> sum1, sum2;
    fenwick_rg(int n) : n(n), sum1(n + 1), sum2(n + 1) {}
    void add(int i, int x) {
        assert(i >= 0 && i < n);
        i++;
        ll v = (ll)i * x;
        for (; i <= n; i += i & -i)
            sum1[i] += x, sum2[i] += v;
    }
    void add(int l, int r, int x) {
        assert(l >= 0 && l <= r && r < n);
        add(l, x);
        if (r + 1 < n) add(r + 1, -x);
    }
    ll query(int p) {
        assert(p >= -1 && p < n);
        p++;
        ll res{};
        for (int i = p; i; i -= i & -i)
            res += (p + 1) * sum1[i] - sum2[i];
        return res;
    }
    ll query(int l, int r) {
        assert(l >= 0 && l <= r && r < n);
        return query(r) - query(l - 1);
    }
};
