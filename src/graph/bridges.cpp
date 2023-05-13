struct Bridge {
    int n, pos=0;
    vector<vector<pair<int, int>>> g; // graph, component
    vector<int> ord, low, bridges; // order, low link, belong to which component
    Bridge(int n) : n(n), g(n), ord(n, -1), low(n) {}
    void add_edge(int u, int v, int i) {
        g[u].emplace_back(v, i);
        g[v].emplace_back(u, i);
    }
    void dfs(int u, int p) {
        ord[u] = low[u] = pos++;
        int cnt = 0;
        for (auto [v, i] : g[u]) {
            // in case there're repeated edges, only skip the first one
            if (v == p && cnt == 0) {
                cnt++;
                continue;
            }
            if (ord[v] == -1) dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > ord[u]) bridges.push_back(i);
        }
    }
    void solve() {
        for (int i = 0; i < n; i++)
            if (ord[i] == -1) dfs(i, i);
    }
};
