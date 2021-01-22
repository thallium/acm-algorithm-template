#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
struct cut_vertex {
    int n, pos=0;
    vector<vector<int>> g;
    vector<int> ord, low, pa;
    vector<int> cuts;
    cut_vertex(int n_) : n(n_), g(n), ord(n, -1), low(n), pa(n, -1) {}
    
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void dfs(int u, int rt) {
        low[u]=ord[u]=pos++;
        int csize=0;
        bool ok=0;
        for (auto v : g[u]) {
            if (v==pa[u]) continue;
            if (ord[v]!=-1) {
                low[u]=min(low[u], ord[v]);
            } else {
                csize++;
                pa[v]=u;
                dfs(v, rt);
                if (u!=rt && low[v]>=ord[u]) ok=true;
                low[u]=min(low[u], low[v]);
            }
        }
        if (ok || (u==rt && csize>1)) cuts.push_back(u);
    }

    void solve() {
        for (int i=0; i<n; i++) {
            if (ord[i]==-1) dfs(i, i);
        }
    }
};
