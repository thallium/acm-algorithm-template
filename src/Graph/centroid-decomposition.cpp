#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    vector<vector<int>> g(n);

    vector<int> vis(n), sz(n);
    auto cal_sz = [&](auto& slf, int u, int p) -> void {
        sz[u] = 1;
        for (auto v : g[u]) {
            if (v == p || vis[v]) {
                continue;
            }
            slf(slf, v, u);
            sz[u] += sz[v];
        }
    };

    auto find_centroid = [&](auto& slf, int u, int p, int n) -> int {
        for (auto v : g[u]) {
            if (vis[v] || v == p) continue;
            if (sz[v] > n / 2) {
                return slf(slf, v, u, n);
            }
        }
        return u;
    };
    auto go = [&](auto& slf, int entry) -> void {
        cal_sz(cal_sz, entry, -1);
        int c = find_centroid(find_centroid, entry, -1, sz[entry]);
        vis[c] = 1;

        // calculte the information of the path, and undo that later

        for (auto v : g[c]) {
            if (!vis[v]) {
                slf(slf, v);
            }
        }
    };

}
