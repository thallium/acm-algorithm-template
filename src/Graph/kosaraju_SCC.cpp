struct kosaraju {
    int n;
    vector<bool> vis;
    vector<int> color, order;
    vector<vector<int>> g, g2, comp;
    kosaraju(int n_) : n(n_), vis(n), color(n, -1), g(n), g2(n) {}
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g2[v].push_back(u);
    }
    void dfs1(int u) {
        vis[u] = true;
        for (int v : g[u])
            if (!vis[v]) dfs1(v);
        order.push_back(u);
    }
    void dfs2(int u) {
        comp.back().push_back(u);
        for (int v : g2[u])
            if (color[v] == -1)
                dfs2(v);
    }
    void solve() {
        for (int i = 0; i < n; ++i)
            if (!vis[i]) dfs1(i);
        for (int i = n - 1; i >= 0; --i)
            if (color[order[i]] == -1) {
                comp.emplace_back();
                dfs2(order[i]);
            }
        // reverse(comp.begin(), comp.end()); to sort components in topological
        // order
        for (int i = 0; i < (int)comp.size(); i++) {
            for (int x : comp[i])
                color[x] = i;
        }
    }
};
