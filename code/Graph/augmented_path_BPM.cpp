#include <bits/stdc++.h>
using namespace std;
// augmented path algorithm for maximum-caredinality bipartite matching
// Worst time complexity: O(nm), but very hard to hack (since we can shuffle),
// usually runs extremely fast, 2e5 vertices and edges in 60 ms.

int main() {
    ios::sync_with_stdio(false);
    int l, r, m;
    cin >> l >> r >> m;
    vector<vector<int>> g(l);
    while (m--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v); // note how we build the graph
    }
    auto aug_path = [](int n, int m, const vector<vector<int>> &g) {
        // we can shuffle vertices:
        // for (auto& v : g)
        //     shuffle(v.begin(), v.end(), rng);
        vector<int> l(n, -1), r(m, -1), vis(n);
        auto match = [&](auto& slf, int u) {
            if (vis[u]) return false;
            vis[u] = true;
            for (auto v : g[u]) {
                if (r[v] == -1) {
                    l[u] = v;
                    r[v] = u;
                    return true;
                }
            }
            for (auto v : g[u]) {
                if (slf(slf, r[v])) {
                    l[u] = v;
                    r[v] = u;
                    return true;
                }
            }
            return false;
        };

        // We can also shuffle the order of visiting vertices
        // vector<int> order(L.size());
        // iota(order.begin(), order.end(), 0);
        // shuffle(order.begin(), order.end(), rng);
        bool ok = true;
        while (ok) {
            ok = false;
            fill(vis.begin(), vis.end(), 0);
            for (int i = 0; i < n; ++i) {
                if (l[i] == -1) ok |= match(match, i);
            }
        }

        std::vector<std::pair<int, int>> matches;
        for (size_t i = 0; i < n; i++) {
            if (l[i] != -1) {
                matches.emplace_back(i, l[i]);
            }
        }
        return matches;
    };
    auto res = aug_path(l, r, g);
}
