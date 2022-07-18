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
