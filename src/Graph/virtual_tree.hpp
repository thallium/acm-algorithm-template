#include "graph/euler_lca.hpp"
#include <vector>

struct VirtualTree {
    int n;
    EulerLCA lca;
    std::vector<std::vector<int>> tree;

    VirtualTree(const std::vector<std::vector<int>> &g, int root)
        : n(g.size()), lca(g, root), tree(n) {}

    auto build_tree(const std::vector<int> &vertices)
        -> std::pair<int, const std::vector<std::vector<int>> &> {
        auto v(vertices);
        std::sort(v.begin(), v.end(), [&](int u, int v) { return lca.pos[u] < lca.pos[v]; });
        int len = v.size();
        for (int i = 1; i < len; i++) {
            v.push_back(lca.lca(v[i - 1], v[i]));
        }
        std::sort(v.begin(), v.end(), [&](int u, int v) { return lca.pos[u] < lca.pos[v]; });
        v.erase(std::unique(v.begin(), v.end()), v.end());
        for (int i = 1; i < (int)v.size(); i++) {
            tree[lca.lca(v[i - 1], v[i])].push_back(v[i]);
        }
        return {v[0], tree};
    }

    void clear(const std::vector<int> v) {
        for (auto u : v) {
            tree[u].clear();
        }
    }

    void clear(int root) {
        for (auto v : tree[root]) {
            clear(v);
        }
        tree[root].clear();
    }
};
