// add an edge (end, start) if to find Eulerian path, and remove it in the answer with:
    // for (auto i : rep(1, ans.size())) {
    //     if (ans[i-1]==n-1 && ans[i]==0) {
    //         for (auto j : rep(i, ans.size()-1)) cout<<ans[j]+1<<' ';
    //         for (auto j : rep(i)) cout<<ans[j]+1<<' ';
    //         return;
    //     }
    // }
struct Euler_tour {
    int n, edge_cnt=0;
    vector<vector<pair<int, int>>> g;
    vector<pair<int, int>> circuit;
    vector<int> deg;
    vector<bool> used;
    // use in-degree and out-degree if directed graph
    // vector<int> indeg, oudeg;
    bool bad=0;

    Euler_tour(int _n) : n(_n), g(n), deg(n) {}

    void add_edge(int u, int v) { // change if directed graph
        g[u].emplace_back(v, edge_cnt);
        g[v].emplace_back(u, edge_cnt);
        deg[u]++, deg[v]++;
        edge_cnt++;
    }
    void dfs(int pre, int u) {
        while (!g[u].empty()) {
            auto [v, edge] = g[u].back();
            g[u].pop_back();
            if (used[edge]) continue;
            used[edge]=true;
            dfs(u, v);
        }
        if (!circuit.empty() && circuit.back().first!=u) bad=true;
        circuit.emplace_back(pre, u);
    }

    vector<int> solve(int start) {
        for (auto x : deg) if (x%2) return {}; // change if directed graph:
        // for (int i=0; i<n; i++) if(indeg[i]!=oudeg[i]) return {};
        used.resize(edge_cnt);
        dfs(-1, start);
        if (circuit.size()!=edge_cnt+1 || bad) return {};
        vector<int> ans;
        for (auto [u, v] : circuit) ans.push_back(v);
        // reverse ans if directed
        // reverse(ans.begin(), ans.end());
        return ans;
    }
};
