#include <vector>
using namespace std;

#include "../DataStructure/fenwick.cpp"
using namespace std;
struct HLD {
    vector<vector<int>> g;
    vector<int> pa, dep, heavy, head, pos, posr; // initialize heavy with -1
    int cnt=0;
    fenwick<long long> tr;
    HLD(int n) : g(n), pa(n), dep(n), heavy(n, -1), head(n), pos(n), posr(n), tr(n) {}
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int dfs(int u) {
        int size = 1;
        int mx = 0;
        for (int v : g[u]) {
            if (v != pa[u]) {
                pa[v] = u, dep[v] = dep[u] + 1;
                int csize = dfs(v);
                size += csize;
                if (csize > mx) mx = csize, heavy[u] = v;
            }
        }
        return size;
    }
    void dfs2(int u, int h) {
        head[u] = h, pos[u] = cnt++; //0-based index
        if (heavy[u] != -1) dfs2(heavy[u], h);
        for (int v : g[u]) {
            if (v != pa[u] && v != heavy[u])
                dfs2(v, v);
        }
        posr[u] = cnt;
    }
    long long pathsum(int u, int v) {
        long long res = 0;
        while (head[u] != head[v]) {
            if (dep[head[u]] < dep[head[v]]) swap(u, v);
            res += tr.query(pos[head[u]], pos[u]);
            u = pa[head[u]];
        }
        if (pos[u] > pos[v]) swap(u, v);
        res += tr.query(pos[u], pos[v]);
        return res;
    }
    int lca(int u, int v) {
        while (head[u] != head[v]) {
            if (dep[head[u]] > dep[head[v]]) u = pa[head[u]];
            else v = pa[head[v]];
        }
        return dep[u] > dep[v] ? v : u;
    }
};
