auto dfs=[&](auto& dfs, int u, int p) -> void {
    if (u==-1) return;
    pa[u][0] = p;
    dep[u] = dep[p] + 1;
    for (int i = 1; i < 20; i++) {
        pa[u][i] = pa[pa[u][i - 1]][i - 1];
    }
    for (auto v : g[u]) {
        if (v == p) continue;
        dfs(dfs, v, u);
    }
};

auto lca=[&](int x, int y) {
    if (dep[x] > dep[y]) swap(x, y);
    int tmp = dep[y] - dep[x];
    for (int j = 0; tmp; ++j, tmp >>= 1) {
        if (tmp & 1) y = pa[y][j];
    }
    if (x == y) return x;
    for (int j = 19; j >= 0 && y != x; j--) {
        if (pa[x][j] != pa[y][j]) {
            x = pa[x][j];
            y = pa[y][j];
        }
    }
    return pa[x][0];
};

