#include <bits/stdc++.h>
using namespace std;
template <typename T> struct diff_2d {
    int n, m;
    vector<vector<T>> dif;
    diff_2d(int n_, int m_)
        : n(n_), m(m_), dif(n + 2, vector<T>(m + 2)) {}
    void add(int x1, int y1, int x2, int y2, T c) {
        x1++, x2++, y1++, y2++;
        dif[x1][y1] += c;
        dif[x2 + 1][y1] -= c;
        dif[x1][y2 + 1] -= c;
        dif[x2 + 1][y2 + 1] += c;
    }

    vector<vector<T>> build() {
        vector res(n, vector<T>(m));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                dif[i][j] += dif[i - 1][j] + dif[i][j - 1] - dif[i - 1][j - 1];
                res[i - 1][j - 1] = dif[i][j];
            }
        }
        return res;
    }
};
