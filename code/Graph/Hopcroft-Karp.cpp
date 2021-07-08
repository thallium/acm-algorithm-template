struct Dinic {
    static constexpr int INF = 1e9;
    int n;
    struct Edge {
        int to, cap;
        Edge(int to, int cap) : to(to), cap(cap) {}
    };
    vector<Edge> e;
    vector<std::vector<int>> g;
    vector<int> cur, h, match; // h = shortest distance from source, calculated in bfs
    // after computing flow, edge (u, v) such that h[u]!=-1 and h[v]==-1 are part of min cut
    Dinic(int n) : n(n), g(n), match(n, -1) {}
    bool bfs(int s, int t) {
        h.assign(n, -1);
        std::queue<int> que;
        h[s] = 0;
        que.push(s);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (int i : g[u]) {
                auto [v, c] = e[i];
                if (c > 0 && h[v] == -1) {
                    h[v] = h[u] + 1;
                    if (v == t) return true;
                    que.push(v);
                }
            }
        }
        return false;
    }
    int dfs(int u, int t, int f) {
        if (u == t) return f;
        int r = f;
        for (int &i = cur[u]; i < int(g[u].size()); ++i) {
            int j = g[u][i];
            auto [v, c] = e[j];
            if (c > 0 && h[v] == h[u] + 1) {
                int a = dfs(v, t, std::min(r, c));
                e[j].cap -= a;
                e[j ^ 1].cap += a;
                r -= a;
                if (a) match[u]=v;
                if (r == 0) return f;
            }
        }
        return f - r;
    }
    void addEdge(int u, int v, int c) {
        g[u].push_back((int)e.size());
        e.emplace_back(v, c);
        g[v].push_back((int)e.size());
        e.emplace_back(u, 0);
    }
    int maxFlow(int s, int t) {
        int ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, INF);
        }
        return ans;
    }
};
struct HopcroftKarp {
    int n, m;
    Dinic flow;
    vector<int> l, r;
    HopcroftKarp(int n, int m) : n(n), m(m), flow(n+m+2), l(n, -1), r(m, -1) {}
    void add_edge(int u, int v) {
        flow.addEdge(u, n+v, 1);
    }
    int solve() {
        for (int i=0; i<n; i++)
            flow.addEdge(n+m, i, 1);
        for (int i=0; i<m; i++)
            flow.addEdge(n+i, n+m+1, 1);
        int res = flow.maxFlow(n+m, n+m+1);
        for (int i=0; i<n; i++) {
            if (flow.match[i]!=-1) {
                l[i]=flow.match[i]-n;
                r[flow.match[i]-n]=i;
            }
        }
        return res;
    }
};
int main() {
    ios::sync_with_stdio(false);
    int l, r, m;
    cin>>l>>r>>m;
    HopcroftKarp g(l, r);
    while (m--) {
        int u, v;
        cin>>u>>v;
        g.add_edge(u, v);
    }
    cout<<g.solve()<<'\n';
    for (int i=0; i<l; i++) {
        if (g.l[i]!=-1) cout<<i<<' '<<g.l[i]<<'\n';
    }
}
