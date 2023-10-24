#include <vector>

using namespace std;

struct hld {
    int n;
    vector<int> pa, head, pos;
    int cnt = 0;

    hld(vector<vector<int>> &g, int root = 0)
      : n((int)g.size()), pa(n), head(n, -1), pos(n) {
        assert(root < (int)g.size());
        pa[root] = root;
        auto dfs = [&](auto &slf, int u) -> int {
            // we use head array as heavy child here to save some space
            int size = 1, max_size = 0;
            for (int v : g[u]) {
                if (v != pa[u]) {
                    pa[v] = u;
                    int csize = slf(slf, v);
                    size += csize;
                    if (csize > max_size) {
                        max_size = csize;
                        head[u] = v;
                    }
                }
            }
            return size;
        };
        dfs(dfs, root);

        auto dfs2 = [&](auto &slf, int u, int h) -> void {
            int hc = exchange(head[u], h);
            pos[u] = cnt++;
            if (hc == -1)
                return;
            slf(slf, hc, h);
            for (int v : g[u]) {
                if (v != pa[u] && v != hc) {
                    slf(slf, v, v);
                }
            }
        };
        dfs2(dfs2, root, root);
    }
    // decompose path from u to v into segment of [l, r] and call process_range
    // use (r > min(pos[u], pos[v])) to test if the segment is from right
    template <typename F>
    int decompose(int u, int v, F&& process_range, bool ignore_lca = false) {
        while (true) {
            if (pos[u] > pos[v]) {
                swap(u, v);
            }
            if (head[u] == head[v]) break;
            int h = head[v];
            process_range(pos[h], pos[v]);
            v = pa[h];
        }
        int l = pos[u] + ignore_lca, r = pos[v];
        if (l <= r) {
            process_range(l, r);
        }
        return v;
    }
};
