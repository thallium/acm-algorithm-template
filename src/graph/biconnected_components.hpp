#pragma once

#include <vector>

static std::vector<std::vector<int>> biconnected_comp(const std::vector<std::vector<int>>& g) {
    const int n = (int)size(g);
    int pos = 0;
    std::vector<int> ord(n, -1), low(n), cuts, stk;
    std::vector<std::vector<int>> comps; // components

    auto dfs = [&](auto& slf, int u, int pa) -> void {
        low[u] = ord[u] = pos++;
        stk.push_back(u);
        int cnt = 0;
        bool is_cut = false;
        for (auto v : g[u]) {
            if (v == pa) continue;
            if (ord[v] == -1) {
                cnt++;
                slf(slf, v, u);
                low[u] = std::min(low[u], low[v]);
                if (low[v] >= ord[u]) {
                    if (u != pa || cnt > 1) is_cut = true;
                    // the subtree will be disconnected if we remove
                    // vertex u, do something if needed
                    comps.emplace_back();
                    while (true) {
                        int back = stk.back();
                        stk.pop_back();
                        comps.back().push_back(back);
                        if (back == v) break;
                    }
                    comps.back().push_back(u);
                }
            } else {
                low[u] = std::min(low[u], ord[v]);
            }
        }
        if (is_cut) cuts.push_back(u);
    };

    for (int i = 0; i < n; i++) {
        if (ord[i] == -1) dfs(dfs, i, i);
    }

    return comps;
}
