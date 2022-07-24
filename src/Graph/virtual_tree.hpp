#include "graph/euler_lca.hpp"
#include <vector>

struct VirtualTree {
    int n;
    EulerLCA lca;
    std::vector<std::vector<int>> tree;

    VirtualTree(const std::vector<std::vector<int>> &g, int root)
        : n(g.size()), lca(g, root), tree(n) {}

    auto build_tree(std::vector<int> &v)
        -> std::pair<int, const std::vector<std::vector<int>>&> {
        std::sort(v.begin(), v.end(), [&](int u, int v) { return lca.pos[u] < lca.pos[v]; });
        std::vector<int> stk;
        for (auto u : v) {
            if (!stk.empty()) {
                int l = lca.lca(stk.back(), u);
                if (l != stk.back()) {
                    while (stk.size() >= 2 && lca.dep[stk[stk.size() - 2]] >= lca.dep[l]) {
                        tree[stk[stk.size() - 2]].push_back(stk.back());
                        stk.pop_back();
                    }
                    if (stk.back() != l) {
                        tree[l].push_back(stk.back());
                        stk.back() = l;
                    }
                }
            }
            stk.push_back(u);
        }
        assert(!stk.empty());
        for (size_t i = 0; i < stk.size() - 1; i++) {
            tree[stk[i]].push_back(stk[i + 1]);
        }
        return {stk[0], tree};
    }

    void clear(int root) {
        for (auto v : tree[root]) {
            clear(v);
        }
        tree[root].clear();
    }
};
