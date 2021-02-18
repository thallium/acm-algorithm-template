constexpr int INF=1e9;
vector<int> dijkstra(const vector<vector<pii>>& g, int start) {
    vector<int> dis(g.size(), INF );
    // vector<pii> pre[N];
    priority_queue<pii, vector<pii>, greater<pii>> q;
    dis[start] = 0;
    q.emplace(0, start);
    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();
        if (d != dis[u]) continue;
        for (auto [v, cost] : g[u]) {
            if (dis[v] > dis[u] + cost) {
                dis[v] = dis[u] + cost;
                // pre[v].clear();
                // pre[v].pb({cost,u});
                q.emplace(dis[v], v);
            }
            // else if(dis[v]==dis[u]+cost)
            // 	pre[v].pb({cost,u});
        }
    }
    return dis;
}
