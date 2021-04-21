#include <vector>
using namespace std;
struct sparse {
    int n, logn;
    vector<vector<int>> f;
    template<typename F>
    sparse(const vector<int> &a, F func) : n((int)a.size()), logn(__lg(n)), f(n, vector<int>(logn+1, 0)) {
        for (int i = 0; i < n; i++)
            f[i][0] = a[i];
        for (int j = 1; j <= logn; j++)
            for (int i = 0; i + (1 << j) - 1 < n; i++)
                f[i][j] = func(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
    }
    int query(int x, int y) {
        int s = __lg(y - x + 1);
        return max(f[x][s], f[y - (1 << s) + 1][s]);
    }
};
