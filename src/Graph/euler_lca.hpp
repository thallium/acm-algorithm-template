#include <vector>
#include <functional>
#include "misc/util.hpp"

template <typename T> struct SparseTable {
    size_t n, logn;
    std::vector<std::vector<T>> v;
    std::function<int(int, int)> F;
    SparseTable() = default;
    SparseTable(const std::vector<T> &a, std::function<int(int, int)> f)
        : n(a.size()), logn(lg(n)), v(logn + 1, std::vector<T>(n)), F(f) {
        v[0] = a;
        for (size_t i = 1; i <= logn; i++)
            for (size_t j = 0; j + (1 << i) - 1 < n; j++)
                v[i][j] = F(v[i - 1][j], v[i - 1][j + (1 << (i - 1))]);
    }
    // get result for [l, r)
    T query(size_t l, size_t r) {
        assert(l < r);
        assert(l < n);
        assert(r <= n);
        int s = lg(r - l);
        return F(v[s][l], v[s][r - (1 << s)]);
    }
};
struct EulerLCA {
    int n;
    std::vector<int> pos, seq, dep;
    SparseTable<int> st;

    EulerLCA(const std::vector<std::vector<int>>& g, int root) : n(g.size()), pos(n), dep(n) {
        seq.reserve(2 * n);
        dfs(root, root, g);
        auto mn = [&](int u, int v) {
            return pos[u] < pos[v] ? u : v;
        };
        st = SparseTable<int>(seq, mn);
    }

    void dfs(int u, int p, const std::vector<std::vector<int>>& g) {
        pos[u] = (int)seq.size();
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
