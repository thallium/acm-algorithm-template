struct Flow {
  static inline constexpr ll INF = INT64_MAX >> 1;
  int n;
  vector<tuple<int, int, int>> e;
  vector<vector<int>> g;
  vector<int> prev;
  vector<ll> h; // distance, also potential
  Flow(int n) : n(n), g(n), h(n), prev(n) {}
  void addEdge(int u, int v, int w, int c) {
    if (u == v) return;
    g[u].emplace_back(e.size());
    e.emplace_back(v, w, c);
    g[v].emplace_back(e.size());
    e.emplace_back(u, 0, -c);
  }
  bool dijkstra(int s, int t) {
    priority_queue<pair<ll, int>> q;
    fill(prev.begin(), prev.end(), -1);
    vector<ll> d(n, INF);
    d[s] = 0;
    q.push({0, s});
    while (!q.empty()) {
      auto [du, u] = q.top();
      q.pop();
      if (d[u] != -du) continue;
      for (auto i : g[u]) {
        auto [v, w, c] = e[i];
        c += h[u] - h[v];
        if (w > 0 && d[v] > d[u] + c) {
          d[v] = d[u] + c;
          prev[v] = i;
          q.push({-d[v], v});
        }
      }
    }
    for (int i = 0; i < n; ++i) {
      if ((h[i] += d[i]) > INF) h[i] = INF;
    }
    return h[t] != INF;
  }
  pair<ll, ll> maxFlow(int s, int t) {
    ll flow = 0, cost = 0;
    while (dijkstra(s, t)) {
      int f = INT_MAX, now = t;
      vector<int> r;
      while (now != s) {
        r.emplace_back(prev[now]);
        f = min(f, get<1>(e[prev[now]]));
        now = get<0>(e[prev[now] ^ 1]);
      }
      for (auto i : r) {
        get<1>(e[i]) -= f;
        get<1>(e[i ^ 1]) += f;
      }
      flow += f;
      cost += ll(f) * h[t];
    }
    return {flow, cost};
  }
};
