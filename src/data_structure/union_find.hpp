#include <vector>
#include <numeric>
struct UF {
    std::vector<int> fa, sz;
    UF(int n) : fa(n), sz(n, 1) { std::iota(fa.begin(), fa.end(), 0); }

    int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

    bool same(int x, int y) { return find(x) == find(y); }

    bool join(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (sz[x] > sz[y]) std::swap(x, y);
        fa[x] = y;
        sz[y] += sz[x];
        return true;
    }
};
