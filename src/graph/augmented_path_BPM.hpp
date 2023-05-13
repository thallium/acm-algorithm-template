// augmented path algorithm for maximum-caredinality bipartite
// matching Worst time complexity: O(nm), but very hard to hack (since
// we can shuffle), usually runs extremely fast, 2e5 vertices and
// edges in 60 ms.
#include <vector>

static auto aug_path(int n, int m, const std::vector<std::vector<int>> g) -> std::pair<int, std::vector<std::pair<int, int>>> {
    std::vector<int> L(n, -1), R(m, -1), vis(n);
    auto match = [&](auto& slf, int u) {
        if (vis[u]) return false;
        vis[u] = true;
        for (auto v : g[u]) {
            if (R[v] == -1) {
                L[u] = v;
                R[v] = u;
                return true;
            }
        }
        for (auto v : g[u]) {
            if (slf(slf, R[v])) {
                L[u] = v;
                R[v] = u;
                return true;
            }
        }
        return false;
    };

    bool ok = true;
    while (ok) {
        ok = false;
        fill(vis.begin(), vis.end(), 0);
        for (int i = 0; i < n; ++i) {
            if (L[i] == -1) ok |= match(match, i);
        }
    }
    int cnt = 0;
    std::vector<std::pair<int, int>> matches;
    for (size_t i = 0; i < n; i++) {
        if (L[i] != -1) {
            cnt++;
            matches.emplace_back(i, L[i]);
        }
    }
    return {cnt, matches};
}
