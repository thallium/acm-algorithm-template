// augmented path algorithm for maximum-caredinality bipartite matching
// Worst time complexity: O(nm), but very hard to hack (since we can shuffle),
// usually runs extremely fast, 2e5 vertices and edges in 60 ms.
#include <bits/stdc++.h>
using namespace std;

mt19937 rng(1);
struct aug_path {
    vector<vector<int>> g;
    vector<int> L, R, vis;

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

    int solve() {
        // shuffle to avoid counter test case, but may be slightly slower
        // for (auto& v : g) 
        //     shuffle(v.begin(), v.end(), rng);
        // vector<int> order(L.size());
        // iota(order.begin(), order.end(), 0);
        // shuffle(order.begin(), order.end(), rng);
        bool ok = true;
        while (ok) {
            ok=false;
            fill(vis.begin(), vis.end(), 0);
            // for (auto i : order)
            for (int i = 0; i < (int)L.size(); ++i)
                if (L[i] == -1) ok |= match(i);
        }

        int ret = 0;
        for (int i = 0; i < L.size(); ++i)
            ret += (L[i] != -1);
        return ret;
    }
};
int main() {
    ios::sync_with_stdio(false);
    int l, r, m;
    cin>>l>>r>>m;
    aug_path g(l, r);
    while (m--) {
        int u, v;
        cin>>u>>v;
        g.add_edge(u, v);
    }
    cout<<g.solve()<<'\n';
    for (int i=0; i<l; i++) {
        if (g.L[i]!=-1) cout<<i<<' '<<g.L[i]<<'\n';
    }
}
