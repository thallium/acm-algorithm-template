// Centroid decomposition
#pragma once

#include <bits/stdc++.h>
#include <utility>

// T has to be be int, array<int, 2>, or pair<int, U>
template <typename T, typename F>
void centroid_decomposition(const std::vector<std::vector<T>> &g, F &&action) {
    auto get_node = [&](T e) {
        if constexpr (std::is_same_v<T, int>) {
            return e;
        }
        auto [u, _] = e;
        return u;
    };

    const int n = (int)size(g);
    std::vector<int> vis(n), sz(n, 1);
    auto cal_sz = [&](auto &slf, int u, int p) -> void {
        for (auto e : g[u]) {
            auto v = get_node(e);
            if (v == p) {
                continue;
            }
            slf(slf, v, u);
            sz[u] += sz[v];
        }
    };
    cal_sz(cal_sz, 0, 0);

    std::vector<std::vector<T>> tree(n);
    auto go = [&](auto& slf, int u) -> void {
        const int s = sz[u];
        int prev = -1;
        while (true) {
            for (auto e : g[u]) {
                auto v = get_node(e);
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
        for (auto e : g[u]) {
            auto v = get_node(e);
            if (!vis[v]) {
                slf(slf, v);
                tree[u].push_back(e);
                if constexpr (std::is_same_v<T, int>) {
                    tree[v].push_back(u);
                } else {
                    auto [vv, x] = e;
                    tree[v].push_back({u, x});
                }
            }
        }
        action(std::as_const(tree), u, s);
    };
    go(go, 0);
}
