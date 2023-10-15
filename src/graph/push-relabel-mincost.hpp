#include <vector>
#include <queue>
#include <limits>

template <typename flow_t = int, typename cost_t = int> struct mcSFlow {
    struct Edge {
        int to;
        cost_t c;
        flow_t f;
        int rev;
    };
    static constexpr cost_t INF = std::numeric_limits<cost_t>::max() / 2;
    static constexpr int scale = 2;
    cost_t eps = 0;
    int n, s, t;
    std::vector<std::vector<Edge>> g;
    std::vector<int> isq, cur;
    std::vector<flow_t> ex;
    std::vector<cost_t> h;
    std::vector<std::vector<int>> hs;
    std::vector<int> co;
    mcSFlow(int n, int s, int t) : n(n), s(s), t(t), g(n) {}
    void add_edge(int a, int b, cost_t cost, flow_t cap) {
        assert(cap >= 0);
        assert(a >= 0 && a < n && b >= 0 && b < n);
        if (a == b) {
            assert(cost >= 0);
            return;
        }
        cost *= n;
        eps = max(eps, abs(cost));
        g[a].emplace_back(b, cost, cap, g[b].size());
        g[b].emplace_back(a, -cost, 0, g[a].size() - 1);
    }
    void add_flow(Edge &e, flow_t f) {
        auto &back = g[e.to][e.rev];
        if (!ex[e.to] && f) hs[h[e.to]].push_back(e.to);
        e.f -= f;
        ex[e.to] += f;
        back.f += f;
        ex[back.to] -= f;
    }
    flow_t max_flow() {
        ex.assign(n, 0);
        h.assign(n, 0);
        hs.resize(2 * n);
        co.assign(2 * n, 0);
        cur.assign(n, 0);
        h[s] = n;
        ex[t] = 1;
        co[0] = n - 1;
        for (auto &e : g[s]) add_flow(e, e.f);
        if (hs[0].size()) {
            for (cost_t hi = 0; hi >= 0;) {
                int u = hs[hi].back();
                hs[hi].pop_back();
                while (ex[u] > 0) { // discharge u
                    if (cur[u] == g[u].size()) {
                        h[u] = 1e9;
                        for (int i = 0; i < g[u].size(); ++i) {
                            auto &e = g[u][i];
                            if (e.f && h[u] > h[e.to] + 1) {
                                h[u] = h[e.to] + 1, cur[u] = i;
                            }
                        }
                        if (++co[h[u]], !--co[hi] && hi < n) {
                            for (int i = 0; i < n; ++i) {
                                if (hi < h[i] && h[i] < n) {
                                    --co[h[i]];
                                    h[i] = n + 1;
                                }
                            }
                        }
                        hi = h[u];
                    } else if (g[u][cur[u]].f && h[u] == h[g[u][cur[u]].to] + 1) {
                        add_flow(g[u][cur[u]], min(ex[u], g[u][cur[u]].f));
                    } else {
                        ++cur[u];
                    }
                }
                while (hi >= 0 && hs[hi].empty()) --hi;
            }
        }
        return -ex[s];
    }
    void push(Edge &e, flow_t x) {
        if (e.f < x) x = e.f;
        e.f -= x;
        ex[e.to] += x;
        g[e.to][e.rev].f += x;
        ex[g[e.to][e.rev].to] -= x;
    }
    void relabel(int v) {
        cost_t nh = -INF; // new height
        for (int i = 0; i < g[v].size(); ++i) {
            const auto &e = g[v][i];
            if (e.f && nh < h[e.to] - e.c) {
                nh = h[e.to] - e.c;
                cur[v] = i;
            }
        }
        h[v] = nh - eps;
    }
    std::pair<flow_t, cost_t> minCostMaxFlow() {
        cost_t cost = 0;
        for (int i = 0; i < n; ++i)
            for (auto &e : g[i])
                cost += e.c * e.f;
        // find max-flow
        flow_t flow = max_flow();
        h.assign(n, 0);
        ex.assign(n, 0);
        isq.assign(n, 0);
        cur.assign(n, 0);
        std::queue<int> q;
        for (; eps; eps >>= scale) {
            // refine
            fill(cur.begin(), cur.end(), 0);
            for (int i = 0; i < n; ++i) {
                for (auto &e : g[i]) {
                    if (h[i] + e.c - h[e.to] < 0 && e.f) push(e, e.f);
                }
            }
            for (int i = 0; i < n; ++i) {
                if (ex[i] > 0) {
                    q.push(i);
                    isq[i] = 1;
                }
            }
            // make flow feasible
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                isq[u] = 0;
                while (ex[u] > 0) {
                    if (cur[u] == g[u].size()) relabel(u);
                    for (int &i = cur[u], max_i = g[u].size(); i < max_i; ++i) {
                        auto &e = g[u][i];
                        if (h[u] + e.c - h[e.to] < 0) {
                            push(e, ex[u]);
                            if (ex[e.to] > 0 && isq[e.to] == 0) {
                                q.push(e.to);
                                isq[e.to] = 1;
                            }
                            if (ex[u] == 0) break;
                        }
                    }
                }
            }
            if (eps > 1 && eps >> scale == 0) {
                eps = 1 << scale;
            }
        }
        for (int i = 0; i < n; ++i) {
            for (auto &e : g[i]) {
                cost -= e.c * e.f;
            }
        }
        return {flow, cost / 2 / n};
    }
    flow_t getFlow(Edge const &e) { return g[e.to][e.rev].f; }
};

