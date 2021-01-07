#include<bits/stdc++.h>
using namespace std;

struct SCC {
    int n, pos=0;
    vector<vector<int>> g;
    vector<bool> vis;
    vector<int> low, ord, stk;
    vector<vector<int>> comp;
    SCC(int _n) : n(_n), g(n), vis(n), low(n), ord(n, -1) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
    }

    void dfs(int u) {
        low[u]=ord[u]=pos++;
        stk.push_back(u);
        vis[u]=true;
        for (auto v : g[u]) {
            if (ord[v]==-1) {
                dfs(v);
                low[u]=min(low[u], low[v]);
            } else if (vis[v]) {
                low[u]=min(low[u], ord[v]);
            }
        }

        if (low[u]==ord[u]) {
            comp.emplace_back();
            while (true) {
                int v=stk.back();
                stk.pop_back();
                vis[v]=false;
                comp.back().push_back(v);
                if (u==v) break;
            }
        }
    }

    void solve() {
        for (int i=0; i<n; i++) {
            if (ord[i]==-1) dfs(i);
        }
        // reverse(comp.begin(), comp.end()); if you need to make sure that for
        // each edge (a, b), the component that contains b cannot be earlier
        // than the component that contains a
    }
};
