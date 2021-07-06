#include <bits/stdc++.h>
using namespace std;
struct cut_vertex {
    int n, pos = 0;
    vector<vector<int>> g;
    vector<int> ord, low, cuts;
    cut_vertex(int n_) : n(n_), g(n), ord(n, -1), low(n) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void dfs(int u, int pa) {
        low[u] = ord[u] = pos++;
        int cnt = 0, sz = 1, sum = 0;
        bool is_cut = 0;
        for (auto v : g[u]) {
            if (v == pa) continue;
            if (ord[v] == -1) {
                cnt++;
                dfs(v, u);
                if (low[v] >= ord[u]) {
                    if (u != pa || cnt > 1) is_cut = true;
                    // the subtree will be disconnected if we remove vertex u,
                    // do something if needed
                }
            }
            low[u] = min(low[u], low[v]);
        }
        if (is_cut) cuts.push_back(u);
    }

    void solve() {
        for (int i = 0; i < n; i++) {
            if (ord[i] == -1) dfs(i, i);
        }
    }
};
