// Tested on: https://vjudge.net/problem/UniversalOJ-80
#include <vector>
#include <limits>

// a is the adjacency matrix where a[i][j] is the cost of mathcing i-th vertex
// in the left to the j-th vertex in the right
// It finds the minimum matching, negate the weight to find maximum matching
// returns {cost, matching} Use a[i][matching[i]] == 0 to test if i-th vertex
// is matched
// Time: O(n^2M)
template<class T>
std::pair<T, std::vector<int>> hungarian(const std::vector<std::vector<T>> &a) {
    if (a.empty()) return {0, {}};
    int n = (int)a.size() + 1, m = (int)a[0].size() + 1;
    assert(m >= n);
    std::vector<T> u(n), v(m); // 顶标
    std::vector<int> p(m), ans(n - 1);
    T INF = std::numeric_limits<T>::max();
    for (int i = 1; i < n; i++) {
        p[0] = i;
        int j0 = 0;
        std::vector<T> dist(m, INF);
        std::vector<int> pre(m, -1);
        std::vector<bool> done(m + 1);
        do { // dijkstra
            done[j0] = true;
            int i0 = p[j0], j1;
            T delta = INF;
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
