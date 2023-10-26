#include <vector>
using namespace std;
inline auto scc(const std::vector<std::vector<int>>& g) -> std::pair<int, std::vector<int>> {
    int n = (int)size(g);
    vector<vector<int>> g2(n);
    for (int i = 0; i < n; i++) {
        for (auto v : g[i]) {
            g2[v].push_back(i);
        }
    }
    vector<int> vis(n), color(n), ord;
    auto dfs = [&](auto& slf, int u) -> void {
        vis[u] = 1;
        for (int v : g[u])
            if (!vis[v]) slf(slf, v);
        ord.push_back(u);
    };
    for (int i = 0; i < n; i++) {
        if (!vis[i]) dfs(dfs, i);
    }

    int c = 0;
    auto dfs2 = [&](auto& slf, int u) -> void {
        color[u] = c;
        for (int v : g2[u])
            if (color[v] == -1)
                slf(slf, v);
    };
    for (int i = n - 1; i >= 0; --i) {
        if (color[ord[i]] == -1) {
            dfs2(dfs2, ord[i]);
            c++;
        }
    }
    return {c, color};
}
