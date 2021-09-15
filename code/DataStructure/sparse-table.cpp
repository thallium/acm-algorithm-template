#include <bits/stdc++.h>
using namespace std;
template <typename T> struct sparse {
    int n, logn;
    vector<vector<T>> v;
    function<T(T, T)> F;
    sparse(const vector<T> &a, function<T(T, T)> func)
        : n((int)a.size()), logn(__lg(n)), v(logn + 1, vector<T>(n + 1)), F(func) {
        v[0] = a;
        for (int i = 1; i <= logn; i++)
            for (int j = 0; j + (1 << i) - 1 < n; j++)
                v[i][j] = F(v[i - 1][j], v[i - 1][j + (1 << (i - 1))]);
    }
    T query(int x, int y) {
        assert(x<=y);
        int s = __lg(y - x + 1);
        return F(v[s][x], v[s][y - (1 << s) + 1]);
    }
};

template<typename T, typename op> struct sparse_2d {
    // using T = int;
    int n, m, logn, logm;
    // vector<vector<vector<vector<T>>>> t;
    static const int N = 1e3 + 5;
    T t[13][13][N][N]; // array layout matches loop order to ensure efficiency

    sparse_2d(vector<vector<T>> val) {
        n = ((int)val.size()), m = ((int)val[0].size()),
        logn = (__lg(n)), logm = (__lg(m));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                t[0][0][i][j] = val[i][j];
        for (int i = 0; i <= logn; i++)
            for (int j = 0; j <= logm; j++) {
                if (i == 0 && j == 0) continue;
                for (int row = 0; row + (1 << i) - 1 < n; row++) {
                    for (int col = 0; col + (1 << j) - 1 < m; col++) {
                        // auto &v = t[row][col];
                        if (i == 0)
                            t[i][j][row][col] = min(t[i][j - 1][row][col],
                                          t[i][j - 1][row][col + (1 << (j - 1))]);
                        if (j == 0)
                            t[i][j][row][col] = min(t[i - 1][j][row][col],
                                          t[i - 1][j][row + (1 << (i - 1))][col]);
                        else
                            t[i][j][row][col] = min(t[i][j - 1][row][col],
                                          t[i][j - 1][row][col + (1 << (j - 1))]);
                    }
                }
            }
    }
    T query(int x1, int x2, int y1, int y2) {
        int kx = __lg(x2 - x1 + 1), ky = __lg(y2 - y1 + 1);
        return min(
            {t[kx][ky][x1][y1], t[kx][ky][x2 - (1 << kx) + 1][y1],
             t[kx][ky][x1][y2 - (1 << ky) + 1],
             t[kx][ky][x2 - (1 << kx) + 1][y2 - (1 << ky) + 1]});
    }

};
