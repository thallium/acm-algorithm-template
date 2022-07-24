#include <vector>
#include "data_structure/sparse-table.hpp"

struct EulerLCA {
    int n;
    std::vector<int> pos, seq, dep;
    SparseTable<int> st;

    EulerLCA(const std::vector<std::vector<int>>& g, int root) : n(g.size()), pos(n), dep(n) {
        seq.reserve(2 * n);
        dfs(root, root, g);
        st = SparseTable<int>(seq, [&](int u, int v) { return pos[u] < pos[v] ? u : v; });
    }

    void dfs(int u, int p, const std::vector<std::vector<int>>& g) {
        pos[u] = seq.size();
        seq.push_back(u);
        for (auto v : g[u]) {
            if (v == p) continue;
            dep[v] = dep[u] + 1;
            dfs(v, u, g);
            seq.push_back(u);
        }
    }

    int lca(int u, int v) {
        if (pos[u] > pos[v]) std::swap(u, v);
        return st.query(pos[u], pos[v] + 1);
    }
};
