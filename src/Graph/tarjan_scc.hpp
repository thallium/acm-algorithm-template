#pragma once
// Note that strictly speaking this is not the tarjan's original algorithm
// because we use a slightly different definition for lowlink. However this
// algorithm is still correctly and easier to code.
// See: https://cs.stackexchange.com/questions/96635/tarjans-scc-example-showing-necessity-of-lowlink-definition-and-calculation-r?rq=1

#include <vector>

// Find strongly connected components of graph g. Components are numbered in reverse topological
// order, starting from 0. It returns the number of components and an array which indicates whichcomponent
// component each vertex belongs to
inline auto scc(const std::vector<std::vector<int>>& g) -> std::pair<int, std::vector<int>> {
    int n = (int)size(g);
    int pos = 0;
    std::vector<bool> on_stk(n);
    std::vector<int> low(n), ord(n, -1), stk;
    std::vector<std::vector<int>> comp;

    auto dfs = [&](auto& slf, int u) -> void {
        low[u] = ord[u] = pos++;
        stk.push_back(u);
        on_stk[u] = true;
        for (auto v : g[u]) {
            if (ord[v] == -1) slf(slf, v);
            if (on_stk[v]) low[u] = std::min(low[u], low[v]);
        }
        if (low[u] == ord[u]) {
            comp.emplace_back();
            while (true) {
                int v = stk.back();
                stk.pop_back();
                on_stk[v] = false;
                comp.back().push_back(v);
                if (u == v) break;
            }
        }
    };

    for (int i = 0; i < n; i++) {
        if (ord[i] == -1) {
            dfs(dfs, i);
        }
    }

    std::vector<int> color(n);
    int cnt = comp.size();
    for (int i = 0; i < cnt; i++) {
        for (auto x : comp[i]) {
            color[x] = i;
        }
    }
    return {cnt, color};
}
