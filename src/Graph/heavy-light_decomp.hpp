#pragma once
#include <vector>
using namespace std;

#include "data_structure/lazy_segtree_non-recursive.hpp"
template <typename T> struct HLD {
    int n;
    vector<int> parent, dep, heavy_child, head, pos, posr;
    int cnt = 0;
    lazy_segtree<T> tr;
    HLD(vector<vector<int>> &g, int root)
        : n(g.size()), parent(n), dep(n), heavy_child(n, -1), head(n),
          pos(n), posr(n), tr(n) {
        assert(root < (int)g.size());
        parent[root] = root;
        dfs(root, g);
        dfs2(root, root, g);
    }
    HLD(vector<vector<int>> &g, int root, vector<typename T::S> &v)
        : HLD(g, root) {
        assert(g.size() == v.size());
        auto a = v;
        for (size_t i = 0; i < v.size(); i++) {
            a[pos[i]] = v[i];
        }
        tr = lazy_segtree<T>(a);
    }
    int dfs(int u, vector<vector<int>> &g) {
        int size = 1;
        int max_size = 0;
        for (int v : g[u]) {
            if (v != parent[u]) {
                parent[v] = u;
                dep[v] = dep[u] + 1;
                int csize = dfs(v, g);
                size += csize;
                if (csize > max_size) {
                    max_size = csize;
                    heavy_child[u] = v;
                }
            }
        }
        return size;
    }
    void dfs2(int u, int h, vector<vector<int>> &g) {
        head[u] = h;
        pos[u] = cnt++;
        if (heavy_child[u] != -1) { dfs2(heavy_child[u], h, g); }
        for (int v : g[u]) {
            if (v != parent[u] && v != heavy_child[u]) {
                dfs2(v, v, g);
            }
        }
        posr[u] = cnt;
    }

    void apply_path(int u, int v, typename T::F f) {
        while (head[u] != head[v]) {
            if (dep[head[u]] < dep[head[v]]) swap(u, v);
            tr.apply(pos[head[u]], pos[u] + 1, f);
            u = parent[head[u]];
        }
        if (pos[u] > pos[v]) swap(u, v);
        tr.apply(pos[u], pos[v] + 1, f);
    }

    typename T::S path_prod(int u, int v) {
        auto res = T::e();
        while (head[u] != head[v]) {
            if (dep[head[u]] < dep[head[v]]) swap(u, v);
            res = T::op(res, tr.prod(pos[head[u]], pos[u] + 1));
            u = parent[head[u]];
        }
        if (pos[u] > pos[v]) swap(u, v);
        res = T::op(res, tr.prod(pos[u], pos[v] + 1));
        return res;
    }

    void apply_subtree(int u, typename T::F f) {
        tr.apply(pos[u], posr[u], f);
    }

    typename T::S subtree_prod(int u) {
        return tr.prod(pos[u], posr[u]);
    }

    typename T::S get(int u) {
        return tr.get(pos[u]);
    }

    int lca(int u, int v) {
        while (head[u] != head[v]) {
            if (dep[head[u]] > dep[head[v]]) u = parent[head[u]];
            else
                v = parent[head[v]];
        }
        return dep[u] > dep[v] ? v : u;
    }
};
