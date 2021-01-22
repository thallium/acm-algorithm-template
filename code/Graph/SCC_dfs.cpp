#include <bits/stdc++.h>
using std::vector;
vector<bool> vis;
vector<int> color,order;
int sccCnt;
void dfs1(int u) {
    vis[u] = true;
    for (int v : g[u])
        if (!vis[v]) dfs1(v);
    order.push_back(u);
}

void dfs2(int u) {
    color[u] = sccCnt;
    for (int v : g2[u])
        if (!color[v]) dfs2(v);
}

void kosaraju() {
    sccCnt = 0;
    for (int i = 0; i < n; ++i)
        if (!vis[i]) dfs1(i);
    for (int i = n-1; i >= 0; --i)
        if (!color[order[i]]) {
            ++sccCnt;
            dfs2(order[i]);
        }
}
