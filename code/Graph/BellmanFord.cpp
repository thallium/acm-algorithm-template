struct BellmanFord {
    static constexpr long long INF=1e18;
    int n;
    vector<tuple<int, int, int>> edges;
    vector<bool> bad; //has negative cycle on the path
    vector<ll> dis;

    BellmanFord(int _n) : n(_n), bad(n), dis(n, INF) {}

    void add_edge(int u, int v, int w) {
        edges.emplace_back(u, v, w);
    }

    void run(int start) {
        dis[start]=0;
        for (int i=0; i<n; i++) {
            for (auto [u, v, w] : edges) {
                if (dis[u]<INF) {
                    dis[v]=min(dis[v], dis[u]+w);
                }
            }
        }

        for (auto [u, v, w] : edges) {
            if (dis[u]<INF) {
                if (dis[v]>dis[u]+w) bad[v]=true;
            }
        }
        for (int i=0; i<n; i++) {
            for (auto [u, v, w] : edges) {
                if (bad[u]) bad[v]=true;
            }
        }
    }

    long long get_dis(int x) {
        return bad[x] ? -INF : dis[x];
    }
};
