#include "misc/util.hpp"
#include <vector>

struct BinaryLifting {
    const int n, level;
    std::vector<std::vector<int>> pa;
    std::vector<int> dep, tin, tout;

    BinaryLifting(const std::vector<std::vector<int>> &g, int root)
        : n((int)g.size()), level(lg(n) + 1),
          pa(n, std::vector<int>(level)), dep(n), tin(n), tout(n) {
        int timer = 0;
        dfs(root, root, g, timer);
    }

    void dfs(int u, int p, const std::vector<std::vector<int>>& g, int& timer) {
        tin[u] = timer++;
        pa[u][0] = p;
        for (int i = 1; i < level; i++) {
            pa[u][i] = pa[pa[u][i - 1]][i - 1];
        }
        for (auto v : g[u]) {
            if (v == p) continue;
            dep[v] = dep[u] + 1;
            dfs(v, u, g, timer);
        }
        tout[u] = timer;
    };

    int go_up(int u, int dis) {
        dis = std::min(dis, (1 << level) - 1);
        for (int j = level - 1; j >= 0; j--) {
            if (dis >> j & 1) {
                u = pa[u][j];
            }
        }
        return u;
    }

    // check if u is ancestor of v
    bool is_ancestor(int u, int v) {
        return tin[v] >= tin[u] && tin[v] < tout[u];
    }

    int lca(int u, int v) {
        if (is_ancestor(u, v)) return u;
        if (is_ancestor(v, u)) return v;
        for (int i = level - 1; i >= 0; i--) {
            if (!is_ancestor(pa[u][i], v)) {
                u = pa[u][i];
            }
        }
        return pa[u][0];
    }

    int dis(int u, int v) {
        int l = lca(u, v);
        return dep[u] - dep[l] + dep[v] - dep[l];
    }
};
