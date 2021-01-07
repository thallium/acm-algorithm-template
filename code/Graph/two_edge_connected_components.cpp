#include <iostream>
#include <vector>
using namespace std;

struct LowLink {
    int n, pos;
    vector<int> ord, low, par, blg; //order, low link, parent, belong to which component
    vector<vector<int>> g, C; //graph, component

    LowLink(int n)
        : n(n), pos(0), ord(n, -1), low(n), par(n, -1), blg(n, -1), g(n) {}

    void add_edge(int u, int v) {
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }

    bool is_bridge(int u, int v) {
        if (ord[u] > ord[v]) swap(u, v);
        return ord[u] < low[v];
    }

    void dfs(int u) {
        ord[u] = low[u] = pos++;
        int cnt = 0;
        for (int v : g[u]) {
            if (v == par[u] && cnt == 0) {
                cnt++;
                continue;
            }
            if (ord[v]!=-1) {
                low[u] = min(low[u], ord[v]);
                continue;
            }
            par[v] = u;
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
    }

    void fill_component(int u) {
        C[blg[u]].emplace_back(u);
        for (int v : g[u]) {
            if (~blg[v] || is_bridge(v, u)) continue;
            blg[v] = blg[u];
            fill_component(v);
        }
    }

    void add_component(int u, int &k) {
        if (~blg[u]) return;
        blg[u] = k++;
        C.emplace_back();
        fill_component(u);
    }

    int build() {
        for (int i = 0; i < n; i++)
            if (ord[i] < 0) dfs(i);

        int k = 0;
        for (int i = 0; i < n; i++)
            add_component(i, k);
        return k;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    LowLink G(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin>>a>>b;
        G.add_edge(a, b);
    }

    int k = G.build();
    cout<<k<<'\n';
    for (int i = 0; i < k; i++) {
        cout<<G.C[i].size()<<' ';
        for (int v : G.C[i]) cout<<v<<' ';
    }
    return 0;
}
