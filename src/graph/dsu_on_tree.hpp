#pragma once
#include <vector>

template<typename f1, typename f2>
std::vector<int> dsu_on_tree(const std::vector<std::vector<int>> &g, f1 &&modify, f2 &&get_result) {
    int n = (int)size(g);
    std::vector<int> sz(n, 1), big(n, -1), l(n), r(n), order(n);
    int timer = 0;
    auto cal_size = [&](auto &slf, int u, int p) -> void {
        order[timer] = u;
        l[u] = timer++;
        for (auto v : g[u]) {
            if (v == p) continue;
            slf(slf, v, u);
            sz[u] += sz[v];
            if (big[u] == -1 || sz[v] > sz[big[u]]) {
                big[u] = v;
            }
        }
        r[u] = timer;
    };
    cal_size(cal_size, 0, 0);
    std::vector<int> ans(n);
    auto dfs = [&](auto &slf, int u, int p) -> void {
        for (auto v : g[u]) {
            if (v == p || v == big[u]) continue;
            slf(slf, v, u);
            for (int i = l[v]; i < r[v]; i++) {
                modify(order[i], 0);
            }
        }
        if (big[u] != -1) {
            slf(slf, big[u], u);
        }
        for (auto v : g[u]) {
            if (v == p || v == big[u]) continue;
            for (int i = l[v]; i < r[v]; i++) {
                modify(order[i], 1);
            }
        }
        modify(u, 1);
        ans[u] = get_result();
    };
    dfs(dfs, 0, 0);
    return ans;
}
