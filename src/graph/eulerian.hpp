#pragma once

#include <vector>
struct Eulerian {
    int n, edge_cnt = 0;
    std::vector<std::vector<std::pair<int, int>>> g;
    std::vector<int> path, deg;
    std::vector<bool> used;
    Eulerian(int _n) : n(_n), g(n), deg(n) {}
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
    std::vector<int> find_cycle(int start) {
        for (auto x : deg)
            if (x % 2) return {};
        used.resize(edge_cnt);
        dfs(start);
        if ((int)path.size() != edge_cnt + 1)
            return {}; // the graph is not connected
        reverse(path.begin(), path.end());
        return path;
    }

    std::vector<int> find_path() {
        std::vector<int> odd_deg;
        for (int i = 0; i < n; i++) {
            if (deg[i] % 2) {
                odd_deg.push_back(i);
            }
        }
        if (odd_deg.size() != 2) {
            return {};
        }
        add_edge(odd_deg[0], odd_deg[1]);
        auto res = find_cycle(odd_deg[1]);
        if (!empty(res))
            res.erase(res.begin()); // the first edge has to be the newly added edge
        return res;
    }

    // returns:
    // - 0 if neither path nor cycle exists
    // - 1 if cycle exists
    // - 2 if path exists
    int exist() {
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (deg[i] % 2) {
                cnt++;
            }
        }
        if (cnt == 0) {
            return 1;
        } else if (cnt == 2) {
            return 2;
        } else {
            return 0;
        }
    }
};
