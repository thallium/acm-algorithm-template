struct BellmanFord {
    static constexpr long long INF=1e18;
    int n, last_relaxed=-1;
    vector<tuple<int, int, int>> edges;
    vector<bool> bad; //has negative cycle on the path
    vector<int> pre;
    vector<ll> dis;

    BellmanFord(int _n) : n(_n), bad(n), pre(n), dis(n, INF) {}

    void add_edge(int u, int v, int w) {
        edges.emplace_back(u, v, w);
    }

    void run(int start) {
        dis[start]=0;
        for (int i=0; i<n-1; i++) {
            for (auto [u, v, w] : edges) {
                if (dis[u]<INF && dis[v]>dis[u]+w) {
                    dis[v]=dis[u]+w;
                    pre[v]=u;
                }
            }
        }

        for (auto [u, v, w] : edges) {
            if (dis[u]<INF && dis[v]>dis[u]+w) {
                dis[v]=dis[u]+w;
                bad[v]=true;
                last_relaxed=v;
                pre[v]=u;
            }
        }
        for (int i=0; i<n; i++) {
            for (auto [u, v, w] : edges) {
                if (bad[u]) bad[v]=true;
            }
        }
    }

    vector<int> find_cycle() {
        dis.assign(n, 0); // without this, only cycle reachable from 0 will be counted
        run(0);
        if (last_relaxed==-1) return {};
        int x=last_relaxed;
        for (int i=0; i<n; i++) x=pre[x];
        vector<int> cycle;
        for (int cur=x; ; cur=pre[cur]) {
            cycle.push_back(cur);
            if (cur==x && cycle.size()>1) break;
        }
        reverse(cycle.begin(), cycle.end());
        return cycle;
    }

    long long get_dis(int x) {
        return bad[x] ? -INF : dis[x];
    }
};
