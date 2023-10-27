#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// a is the adjacency matrix where a[i][j] is the cost of mathcing i-th vertex
// in the left to the j-th vertex in the right
// It finds the minimum matching, negate the weight to find maximum matching
// returns {cost, matching} Use a[i][matching[i]] == 0 to test if i-th vertex
// is matched
// Time: O(n^2M)
template<class T>
pair<T, vector<int>> hungarian(const vector<vector<T>> &a) {
    if (a.empty()) return {0, {}};
    int n = a.size() + 1, m = a[0].size() + 1;
    assert(m >= n);
    vector<T> u(n), v(m); // 顶标
    vector<int> p(m), ans(n - 1);
    for (int i = 1; i < n; i++) {
        p[0] = i;
        int j0 = 0;
        vector<T> dist(m, numeric_limits<T>::max());
        vector<int> pre(m, -1);
        vector<bool> done(m + 1);
        do { // dijkstra
            done[j0] = true;
            int i0 = p[j0], j1;
            T delta = numeric_limits<T>::max();
            for (int j = 1; j < m; j++)
                if (!done[j]) {
                    auto cur = a[i0 - 1][j - 1] - u[i0] - v[j];
                    if (cur < dist[j]) dist[j] = cur, pre[j] = j0;
                    if (dist[j] < delta) delta = dist[j], j1 = j;
                }
            for (int j = 0; j < m; j++) {
                if (done[j]) u[p[j]] += delta, v[j] -= delta;
                else dist[j] -= delta;
            }
            j0 = j1;
        } while (p[j0]);
        while (j0) { // update alternating path
            int j1 = pre[j0];
            p[j0] = p[j1], j0 = j1;
        }
    }
    for (int j = 1; j < m; j++) {
        if (p[j]) ans[p[j] - 1] = j - 1;
    }
    return {-v[0], ans}; // min cost
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int l, r, m;
    cin >> l >> r >> m;
    vector g(l, vector<ll>(max(l, r), 0));

    while (m--) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        u--, v--;
        g[u][v] = min(g[u][v], -w);
    }

    auto [ans, res] = hungarian(g);
    cout << -ans << '\n';
    for (int i = 0; i < l; i++) {
        int v = res[i];
        cout << (g[i][v] == 0 ? 0 : v + 1) << " \n"[i == l - 1];
    }
    return 0;
}
