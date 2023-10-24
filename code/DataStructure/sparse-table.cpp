#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    vector<int> a(n);

    int logn = __lg(n);
    vector v(logn + 1, vector<int>(n));
    v[0] = a;
    for (size_t i = 1; i <= logn; i++)
        for (size_t j = 0; j + (1 << i) - 1 < n; j++)
            v[i][j] = max(v[i - 1][j], v[i - 1][j + (1 << (i - 1))]);

    // [l, r]
    auto query = [&](int l, int r) {
        assert(l <= r);
        int s = __lg(r - l + 1);
        return max(v[s][l], v[s][r - (1 << s) + 1]);
    };
}

namespace st { // 2d sparse table
    using T = int;
    int n, m, logn, logm;
    static const int N = 1e3 + 5;
    T t[13][13][N][N]; // array layout matches loop order to ensure efficiency

    template<typename U>
    void init(const vector<vector<U>>& val) {
        n = ((int)val.size()), m = ((int)val[0].size()),
        logn = (__lg(n)), logm = (__lg(m));
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) t[0][0][i][j] = val[i][j];
        for (int i = 0; i <= logn; i++)
            for (int j = 0; j <= logm; j++) {
                if (i == 0 && j == 0) continue;
                for (int row = 0; row + (1 << i) - 1 < n; row++) {
                    for (int col = 0; col + (1 << j) - 1 < m; col++) {
                        // auto &v = t[row][col];
                        if (i == 0)
                            t[i][j][row][col] = min(t[i][j - 1][row][col], t[i][j - 1][row][col + (1 << (j - 1))]);
                        if (j == 0)
                            t[i][j][row][col] = min(t[i - 1][j][row][col], t[i - 1][j][row + (1 << (i - 1))][col]);
                        else
                            t[i][j][row][col] = min(t[i][j - 1][row][col], t[i][j - 1][row][col + (1 << (j - 1))]);
                    }
                }
            }
    }
    T query(int x1, int x2, int y1, int y2) {
        assert(n!=0 && m!=0);
        assert(x1 <= x2);
        assert(y1 <= y2);
        assert(x1 >= 0 && x1 < n);
        assert(x2 >= 0 && x2 < n);
        assert(y1 >= 0 && y1 < m);
        assert(y2 >= 0 && y2 < m);
        int kx = __lg(x2 - x1 + 1), ky = __lg(y2 - y1 + 1);
        return min(
            {t[kx][ky][x1][y1], t[kx][ky][x2 - (1 << kx) + 1][y1],
             t[kx][ky][x1][y2 - (1 << ky) + 1],
             t[kx][ky][x2 - (1 << kx) + 1][y2 - (1 << ky) + 1]});
    }

};
