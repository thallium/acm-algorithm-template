#pragma once
#include <vector>
#include <queue>

template <typename G>
std::vector<long long> dijkstra(const G &g, int start) {
    constexpr long long INF = 1e18;
    std::vector dis(g.size(), INF);
    // std::vector<pii> pre[N];
    using node = std::pair<long long, int>;
    std::priority_queue<node, std::vector<node>, std::greater<>> q;
    dis[start] = 0;
    q.emplace(0, start);
    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();
        if (d != dis[u]) continue;
        for (auto [v, cost] : g[u]) {
            if (dis[v] > d + cost) {
                dis[v] = d + cost;
                // pre[v].clear();
                // pre[v].pb({cost,u});
                q.emplace(dis[v], v);
            }
            // else if(dis[v]==dis[u]+cost)
            // pre[v].pb({cost,u});
        }
    }
    return dis;
}
// dijkstra for small edge weight (less than 10) aka 1-k bfs
inline std::vector<int>
SmallDijkstra(const std::vector<std::vector<std::pair<int, int>>> &g,
              int src, int lim) {
    std::vector<std::vector<int>> qs(lim);
    std::vector<int> dis(g.size(), -1);
    dis[src] = 0;
    qs[0].push_back(src);
    for (int d = 0, maxd = 0; d <= maxd; ++d) {
        for (auto &q = qs[d % lim]; q.size();) {
            int u = q.back();
            q.pop_back();
            if (dis[u] != d) continue;
            for (auto [v, c] : g[u]) {
                if (dis[v] != -1 && dis[v] <= d + c) continue;
                dis[v] = d + c;
                qs[(d + c) % lim].push_back(v);
                maxd = std::max(maxd, d + c);
            }
        }
    }
    return dis;
}
