struct Eulerian_path {
    int n, edge_cnt = 0;
    vector<vector<pair<int, int>>> g;
    vector<int> path, deg;
    vector<bool> used;
    Eulerian_path(int _n) : n(_n), g(n), deg(n) {}
    void add_edge(int u, int v) {
        g[u].emplace_back(v, edge_cnt);
        g[v].emplace_back(u, edge_cnt);
        deg[u]++, deg[v]++;
        edge_cnt++;
    }
    void dfs(int u) {
        while (!g[u].empty()) {
            auto [v, edge] = g[u].back();
            g[u].pop_back();
            if (used[edge]) continue;
            used[edge] = true;
            dfs(v);
        }
        path.push_back(u);
    }
    vector<int> solve(int start) {
        for (auto x : deg)
            if (x % 2) return {};
        used.resize(edge_cnt);
        dfs(start);
        if ((int)path.size() != edge_cnt + 1)
            return {}; // the graph is not connected
        reverse(path.begin(), path.end());
        return path;
    }

    vector<int> solve(int start, int end) {
        add_edge(start, end);
        auto res = solve(end);
        if (!empty(res))
            res.erase(res.begin()); // the first edge has to be the newly added edge
        return res;
    }
};
