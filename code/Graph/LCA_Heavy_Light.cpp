#include <bits/stdc++.h>
using std::vector;
vector<vector<int>> g;
vector<int> fa, dep, heavy, head; // remember to initialize heavy with -1

int dfs(int u) {
    int size = 1, mx = 0;
    for (int v : g[u]) {
        if (v == fa[u]) continue;
        fa[v] = u, dep[v] = dep[u] + 1;
        int csize = dfs(v);
        size += csize;
        if (csize > mx) {
            mx = csize;
            heavy[u] = v;
        }
    }
    return size;
}
void dfs2(int u, int h) {
    head[u] = h;
    if (heavy[u] != -1) dfs2(heavy[u], h);
    for (int v : g[u]) 
        if (v != fa[u] && v != heavy[u]) dfs2(v, v);
}
int lca(int u, int v) {
    while (head[u] != head[v]) {
        if (dep[head[u]] > dep[head[v]]) u = fa[head[u]];
        else v = fa[head[v]];
    }
    return dep[u] > dep[v] ? v : u;
}
