#include <bits/stdc++.h>
using namespace std;
template <typename T> struct sparse {
    int n, logn;
    vector<vector<T>> v;
    function<T(T, T)> F;
    sparse(const vector<int> &a, function<T(T, T)> func)
        : n((int)a.size()), logn(__lg(n)), v(logn + 1, vector<T>(n + 1)), F(func) {
        v[0] = a;
        for (int i = 1; i <= logn; i++)
            for (int j = 0; j + (1 << i) - 1 < n; j++)
                v[i][j] = F(v[i - 1][j], v[i - 1][j + (1 << (i - 1))]);
    }
    int query(int x, int y) {
        int s = __lg(y - x + 1);
        return F(v[s][x], v[s][y - (1 << s) + 1]);
    }
};
