// augmented path algorithm for maximum-caredinality bipartite
// matching Worst time complexity: O(nm), but very hard to hack (since
// we can shuffle), usually runs extremely fast, 2e5 vertices and
// edges in 60 ms.
#include <random>
#include <vector>
struct aug_path {
    std::vector<std::vector<int>> g;
    std::vector<int> L, R, vis;
    aug_path(int n, int m) : g(n), L(n, -1), R(m, -1), vis(n) {}
    void add_edge(int a, int b) { g[a].push_back(b); }
    bool match(int u) {
        if (vis[u]) return false;
        vis[u] = true;
        for (auto v : g[u]) {
            if (R[v] == -1) {
                L[u] = v;
                R[v] = u;
                return true;
            }
        }
        for (auto vec : g[u]) {
            if (match(R[vec])) {
                L[u] = vec;
                R[vec] = u;
                return true;
            }
        }
        return false;
    }

    // shuffle to avoid counter test case, but may be slightly slower
    template<bool to_shuffle = false>
    int solve() {
        std::vector<int> order;
        if constexpr (to_shuffle) {
            std::mt19937 rng(1);
            for (auto& v : g)
                shuffle(v.begin(), v.end(), rng);
            order.resize(L.size());
            iota(order.begin(), order.end(), 0);
            shuffle(order.begin(), order.end(), rng);
        }
        bool ok = true;
        while (ok) {
            ok = false;
            fill(vis.begin(), vis.end(), 0);
            if constexpr (to_shuffle) {
                for (auto i : order) {
                    if (L[i] == -1) ok |= match(i);
                }
            } else {
                for (int i = 0; i < (int)L.size(); ++i) {
                    if (L[i] == -1) ok |= match(i);
                }
            }
        }
        int ret = 0;
        for (int i = 0; i < L.size(); ++i)
            ret += (L[i] != -1);
        return ret;
    }
};
