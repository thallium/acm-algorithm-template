#pragma once
#include <vector>
using namespace std;

template <typename T> struct HLD {
    int n;
    vector<int> parent, head, pos, posr;
    int cnt = 0;

    HLD(vector<vector<int>> &g, int root = 0)
        : n((int)g.size()), parent(n), head(n), pos(n), posr(n) {
        assert(root < (int)g.size());
        parent[root] = root;
        dfs(root, g);
        dfs2(root, root, g);
    }

    int dfs(int u, const vector<vector<int>> &g) {
        // we use head array as heavy child here to save some space
        int size = 1, max_size = 0;
        for (int v : g[u]) {
            if (v != parent[u]) {
                parent[v] = u;
                int csize = dfs(v, g);
                size += csize;
                if (csize > max_size) {
                    max_size = csize;
                    head[u] = v;
                }
            }
        }
        return size;
    }

    void dfs2(int u, int h, const vector<vector<int>> &g) {
        int heavy_child = exchange(head[u], h);
        pos[u] = cnt++;
        if (heavy_child == -1) return;
        dfs2(heavy_child, h, g);
        for (int v : g[u]) {
            if (v != parent[u] && v != heavy_child) {
                dfs2(v, v, g);
            }
        }
        posr[u] = cnt;
    }

    // decompose path from u to v into segment of [l, r) and call process_range
    template <typename F>
    int decompose(int u, int v, F&& process_range, bool ignore_lca = false) {
        while (true) {
            if (pos[head[u]] < pos[head[v]]) swap(u, v);
            if (head[u] == head[v]) break;
            int h = head[u];
            process_range(pos[h], pos[u] + 1);
            u = parent[h];
        }
        int l = pos[v] + ignore_lca, r = pos[u] + 1;
        if (l < r) {
            process_range(l, r);
        }
        return v;
    }

    // void apply_path(int u, int v, typename T::F f) {
    //     while (head[u] != head[v]) {
    //         if (dep[head[u]] < dep[head[v]]) swap(u, v);
    //         tr.apply(pos[head[u]], pos[u] + 1, f);
    //         u = parent[head[u]];
    //     }
    //     if (pos[u] > pos[v]) swap(u, v);
    //     tr.apply(pos[u], pos[v] + 1, f);
    // }

    // return the 
    int id(int u) {
        return pos[u];
    }

    int lca(int u, int v) {
        return decompose(u, v, [](int l, int r) {});
    }
};
