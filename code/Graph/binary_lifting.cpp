#include <bits/stdc++.h>
using namespace std;

int __lg(int);
int op(int, int);
int e();
int main() {
    int n;
    vector<vector<array<int, 2>>> g(n);

    const int lg = __lg(n);
    vector pa(n, vector(lg + 1, 0));
    vector data(n, vector(lg + 1, 0)); // data[u][i]: data of path from u to pa[u][i]
    data[0][0] = e();                  // set data[root][0] to identity element
    vector<int> dep(n);

    auto dfs = [&](auto& slf, int u, int p) -> void {
        pa[u][0] = p;
        for (int i = 1; i <= lg; i++) {
            pa[u][i] = pa[pa[u][i - 1]][i - 1];
            data[u][i] = op(data[u][i - 1], data[pa[u][i - 1]][i - 1]);
        }

        for (auto [v, w] : g[u]) {
            if (v == p) continue;
            data[v][0] = w;
            dep[v] = dep[u] + 1;
            slf(slf, v, u);
        }
    };

    dfs(dfs, 0, 0);

    auto jump = [&](int u, int d) {
        auto s = e();
        for (int i = lg; i >= 0; i--) {
            if (d >> i & 1) {
                s = op(s, data[u][i]);
                u = pa[u][i];
            }
        }
        return pair{u, s};
    };

    auto lca = [&](int u, int v) {
        if (dep[u] < dep[v]) {
            swap(u, v);
        }
        int s = e();
        tie(u, s) = jump(u, dep[u] - dep[v]);

        if (u == v) return pair{u, s};

        for (int i = lg; i >= 0; i--) {
            if (pa[u][i] != pa[v][i]) {
                s = op(op(s, data[u][i]), data[v][i]);
                u = pa[u][i];
                v = pa[v][i];
            }
        }

        s = op(op(s, data[u][0]), data[v][0]);
        return pair{pa[u][0], s};
    };
}
