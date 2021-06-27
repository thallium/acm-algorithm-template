#include <bits/stdc++.h>
using namespace std;
struct Binary_lifting {
    const int sz, level;
    const vector<vector<int>>& g;
    vector<vector<int>> pa;
    vector<int> dep;

    Binary_lifting(const vector<vector<int>>& g_) :
        sz((int)g_.size()),
        level(__lg(sz)+2),
        g(g_),
        pa(sz, vector<int>(level)),
        dep(g.size()) {}

    void dfs(int u, int p) {
        pa[u][0] = p;
        dep[u] = dep[p] + 1;
        for (int i = 1; i < level; i++) {
            pa[u][i] = pa[pa[u][i - 1]][i - 1];
        }
        for (auto v : g[u]) {
            if (v == p) continue;
            dfs(v, u);
        }
    };

    int jump(int u, int step) {
        for (int i=0; i<level; i++) {
            if (step>>i&1) u=pa[u][i];
        }
        return u;
    }

    int lca(int x, int y) {
        if (dep[x] > dep[y]) swap(x, y);
        y=jump(y, dep[y] - dep[x]);
        if (x == y) return x;
        for (int i=level-1; i>=0; i--) {
            if (pa[x][i] != pa[y][i]) {
                x = pa[x][i];
                y = pa[y][i];
            }
        }
        return pa[x][0];
    }
};

