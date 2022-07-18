int main() {
    vector<int> bch(n, -1);
    int cur_big = -1;
    auto get_big = [&](auto &dfs, int u, int p) -> int {
        int sz = 1, mx = 0;
        for (auto v : g[u]) {
            if (v == p) continue;
            int csz = dfs(dfs, v, u);
            if (csz > mx) mx = csz, bch[u] = v;
            sz += csz;
        }
        return sz;
    };
    auto add = [&](auto &slf, int u, int p, int x) -> void {
        // update info of u here
        for (auto v : g[u]) {
            if (v == p || v == cur_big) continue;
            slf(slf, v, u, x);
        }
    };
    auto dfs = [&](auto &dfs, int u, int pa, bool keep) -> void {
        int big = bch[u];
        for (auto v : g[u])
            if (v != pa && v != big) dfs(dfs, v, u, 0);
        if (big != -1) {
            dfs(dfs, big, u, 1);
            cur_big = big;
        }
        add(add, u, pa, 1);
        // now you get all the info of subtree of u, answer queries about u
        // here.
        cur_big = -1;
        if (!keep) add(add, u, pa, -1);
    };
}
