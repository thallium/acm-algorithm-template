#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    vector<vector<int>> g(n);

    vector<int> sz(n, 1), big(n, -1);
    auto cal_size = [&](auto &slf, int u, int p) -> void {
        for (auto v : g[u]) {
            if (v == p)
                continue;
            slf(slf, v, u);
            sz[u] += sz[v];
            if (big[u] == -1 || sz[v] > sz[big[u]]) {
                big[u] = v;
            }
        }
    };
    cal_size(cal_size, 0, 0);
    auto modify = [&](auto &slf, int u, int p, int add) -> void {
        if (add) {
            // add u to result
        } else {
            // remove u from result
        }
        for (auto v : g[u]) {
            if (v == p)
                continue;
            slf(slf, v, u, add);
        }
    };
    auto dfs = [&](auto &slf, int u, int p) -> void {
        for (auto v : g[u]) {
            if (v == p || v == big[u])
                continue;
            slf(slf, v, u);          // tranverse light child
            modify(modify, v, u, 0); // remove light child
        }
        if (big[u] != -1) {
            slf(slf, big[u], u); // remove heavy child
        }
        for (auto v : g[u]) {
            if (v == p || v == big[u])
                continue;
            modify(modify, v, u, 1); // add light child again
        }
        // add u to result
        // now we have the result for subtree of u
    };
    dfs(dfs, 0, 0);
}
