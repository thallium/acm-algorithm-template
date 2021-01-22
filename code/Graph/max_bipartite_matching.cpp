#include <vector>
#include <cassert>
using std::vector;
struct augment_path {
    int n, m;         // number of vertices of two sets
    int dfn;          // time
    vector<vector<int> > g;
    vector<int> pa, pb;  // matchings
    vector<int> vis;

    augment_path(int _n, int _m) : n(_n), m(_m), dfn(0), pa(n, -1), pb(m, -1), vis(n), g(n) { }

    void add(int from, int to) {
        assert(0 <= from && from < n && 0 <= to && to < m);
        g[from].push_back(to);
    }

    bool dfs(int v) {
        vis[v] = dfn;
        for (int u : g[v]) {
            if (pb[u] == -1) {
                pb[u] = v;
                pa[v] = u;
                return true;
            }
        }
        for (int u : g[v]) {
            if (vis[pb[u]] != dfn && dfs(pb[u])) {
                pa[v] = u;
                pb[u] = v;
                return true;
            }
        }
        return false;
    }

    int solve() {
        int res=0;
        while (true) {
            dfn++;
            int cnt = 0;
            for (int i = 0; i < n; i++) {
                if (pa[i] == -1 && dfs(i)) {
                    cnt++;
                }
            }
            if (cnt == 0) {
                break;
            }
            res += cnt;
        }
        return res;
    }
};

