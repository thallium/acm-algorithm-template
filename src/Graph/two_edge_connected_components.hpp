#include <vector>
#include <iostream>

struct TECC {
    int n, pos=0;
    std::vector<int> ord, low, color; // order, low link, belong to which component
    std::vector<std::vector<int>> g, comp; // graph, component
    TECC(int n) : n(n), ord(n, -1), low(n), color(n, -1), g(n) {}
    void add_edge(int u, int v) {
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    bool is_bridge(int u, int v) {
        if (ord[u] > ord[v]) std::swap(u, v);
        return ord[u] < low[v];
    }
    void dfs(int u, int p) {
        ord[u] = low[u] = pos++;
        int cnt = 0;
        for (int v : g[u]) {
            // in case there're repeated edges, only skip the first one
            if (v == p && cnt == 0) {
                cnt++;
                continue;
            }
            if (ord[v] == -1) dfs(v, u);
            low[u] = std::min(low[u], low[v]);
        }
    }
    void fill_component(int u) {
        comp.back().emplace_back(u);
        for (int v : g[u]) {
            if (color[v] != -1 || is_bridge(v, u)) continue;
            color[v] = color[u];
            fill_component(v);
        }
    }
    int build() {
        for (int i = 0; i < n; i++)
            if (ord[i] == -1) dfs(i, i);
        int k = 0;
        for (int i = 0; i < n; i++) {
            if (color[i] != -1) continue;
            color[i] = k++;
            comp.emplace_back();
            fill_component(i);
        }
        return k;
    }
};
// Example:
// int main() {
//     using std::cin, std::cout;
//     int n, m;
//     cin >> n >> m;
//     TECC g(n);
//     for (int i = 0; i < m; i++) {
//         int a, b;
//         cin >> a >> b;
//         g.add_edge(a, b);
//     }
//     int k = g.build();
//     cout << k << '\n';
//     for (int i = 0; i < k; i++) {
//         cout << g.comp[i].size() << ' ';
//         for (int v : g.comp[i])
//             cout << v << ' ';
//     }
//     return 0;
// }
