#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    vector<vector<array<int, 2>>> g;

    auto decomp = [&](auto& f) {
        vector<int> vis(n), sz(n, 1);
        auto cal_sz = [&](auto& slf, int u, int p) -> void {
            for (auto [v, w] : g[u]) {
                if (v == p) continue;
                slf(slf, v, u);
                sz[u] += sz[v];
            }
        };
        cal_sz(cal_sz, 0, 0);

        vector<vector<array<int, 2>>> tr(n);
        auto go = [&](auto& slf, int u) -> void {
            int s = sz[u];
            int prev = -1;
            while (1) {
                for (auto [v, w] : g[u]) {
                    if (!vis[v] && sz[v] * 2 > s) {
                        sz[u] -= sz[v];
                        sz[v] = s;
                        u = v;
                    }
                }
                if (u == prev) break;
                prev = u;
            }

            vis[u] = 1;
            for (auto [v, w] : g[u]) {
                if (!vis[v]) {
                    slf(slf, v);
                    tr[u].push_back({v, w});
                    tr[v].push_back({u, w});
                }
            }
            f(tr, u, s); // u is the root of the current tree, s is the size of the tree
        };
        go(go, 0);
    };
}
