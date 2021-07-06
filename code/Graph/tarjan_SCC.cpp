#include <bits/stdc++.h>
using namespace std;

struct SCC {
    int n, pos = 0;
    vector<vector<int>> g;
    vector<bool> on_stk;
    vector<int> low, ord, stk, color;
    vector<vector<int>> comp;
    SCC(int _n) : n(_n), g(n), on_stk(n), low(n), ord(n, -1), color(n) {}

    void add_edge(int u, int v) { g[u].push_back(v); }

    void dfs(int u) {
        low[u] = ord[u] = pos++;
        stk.push_back(u);
        on_stk[u] = true;
        for (auto v : g[u]) {
            if (ord[v] == -1) dfs(v);
            if (on_stk[v]) {
                low[u] = min(low[u], low[v]);
            }
        }

        if (low[u] == ord[u]) {
            comp.emplace_back();
            while (true) {
                int v = stk.back();
                stk.pop_back();
                on_stk[v] = false;
                comp.back().push_back(v);
                if (u == v) break;
            }
        }
    }

    void solve() {
        for (int i = 0; i < n; i++)
            if (ord[i] == -1) dfs(i);
        // reverse(comp.begin(), comp.end()); to sort components in topological
        // order
        for (int i = 0; i < (int)comp.size(); i++) {
            for (int x : comp[i])
                color[x] = i;
        }
    }
};
