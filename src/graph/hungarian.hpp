// credits:
// https://github.com/the-tourist/algo/blob/master/flows/hungarian.cpp
// hungarian algorithm for bipartite graph matching, matches every
// node on the left with a node on the right and the sum of the
// weights is minimal. a[i][j] is the cost for i in L to be matched
// with j in R. (0-indexed) pa[i] is the node in R matched with i
// pb[j] is the node in L matched with j
// Negate the cost for max cost.
// Time: O(n^2M)
#include <vector>
#include <limits>

template <typename T> struct Hungarian {
    int n, m;
    std::vector<std::vector<T>> a;
    std::vector<T> u, v;
    std::vector<int> pa, pb, way;
    std::vector<T> minv;
    std::vector<bool> used;
    T inf;
    Hungarian(int _n, int _m)
        : n(_n), m(_m), a(n, std::vector<T>(m)), u(n + 1), v(m + 1),
          pa(n + 1, -1), pb(m + 1, -1), way(m, -1), minv(m),
          used(m + 1) {
        assert(n <= m);
        inf = std::numeric_limits<T>::max();
    }
    inline void add_row(int i) {
        fill(minv.begin(), minv.end(), inf);
        fill(used.begin(), used.end(), false);
        pb[m] = i;
        pa[i] = m;
        int j0 = m;
        do {
            used[j0] = true;
            int i0 = pb[j0];
            T delta = inf;
            int j1 = -1;
            for (int j = 0; j < m; j++) {
                if (!used[j]) {
                    T cur = a[i0][j] - u[i0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }
            for (int j = 0; j <= m; j++) {
                if (used[j]) {
                    u[pb[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        } while (pb[j0] != -1);
        do {
            int j1 = way[j0];
            pb[j0] = pb[j1];
            pa[pb[j0]] = j0;
            j0 = j1;
        } while (j0 != m);
    }
    inline T current_score() { return -v[m]; }
    inline T solve() {
        for (int i = 0; i < n; i++) {
            add_row(i);
        }
        return current_score();
    }
};
