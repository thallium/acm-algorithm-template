#include <bits/stdc++.h>
using namespace std;

template <typename T> struct fenwick {
  int n;
  vector<T> t;

  fenwick(int n_) : n(n_), t(n) {}
  fenwick(const vector<int> &v) : fenwick((int)v.size()) {
    for (int i = 0; i < n; i++) {
      t[i] += v[i];
      int j = i | (i + 1);
      if (j < n)
        t[j] += t[i];
    }
  }

  void update(int i, T x) {
    while (i < n) {
      t[i] += x;
      i |= (i + 1);
    }
  }

  template <typename U> U query(int i) {
    U res{};
    for (; i >= 0; i = (i & (i + 1)) - 1)
      res += t[i];
    return res;
  }

  template <typename U>
  U query(int l, int r) { return query<U>(r) - (l ? query<U>(l - 1) : U{}); }

  int search(T prefix) { // equivalent to upper_bound(prefix)
    int pos = 0;
    T sum = 0;
    for (int i = 20; i >= 0; i--) {
      if (pos + (1 << i) <= n && (sum + t[pos + (1 << i)] <= prefix)) {
        pos += (1 << i);
        sum += t[pos];
      }
    }
    return pos + 1;
  }
};

// fenwick tree with range update and range sum query
template <typename T> struct fenwick_rg {
    int n;
    vector<T> sum1, sum2;
    fenwick_rg(int n_) : n(n_), sum1(n+1), sum2(n+1) {}

    void update(int p, T x) {
        p++;
        for (int i = p; i <= n; i += i & -i)
            sum1[i] += x, sum2[i] += x * p;
    }
    void update(int l, int r, T x) { update(l, x), update(r + 1, -x); }

    T query(int p) {
        p++;
        T res{};
        for (int i = p; i; i -= i & -i)
            res += (p + 1) * sum1[i] - sum2[i];
        return res;
    }

    T query(int l, int r) { return query(r) - query(l - 1); }
};
