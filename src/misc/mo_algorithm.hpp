#include <cmath>
#include <array>
#include <vector>

// Mo's algorithm, solve m offline queries on array of length n in O(n sqrt(m))
template <typename T, typename F>
std::vector<T> mo_alg(int n, const std::vector<std::array<int, 2>>& query, F &&move) {
    struct node {
        int l, r, id;
    };

    int m = (int)size(query);
    std::vector<node> q(m);
    for (int i = 0; i < m; i++) {
        q[i] = {query[i][0], query[i][1], i};
    }

    const int BLOCK_SIZE = (n <= m ? ceil(sqrt(n)) : n / ceil(sqrt(m)));
    sort(q.begin(), q.end(), [&](const node &lhs, const node &rhs) {
        if (lhs.l / BLOCK_SIZE != rhs.l / BLOCK_SIZE)
            return lhs.l < rhs.l;
        return ((lhs.l / BLOCK_SIZE) & 1) ? lhs.r < rhs.r : lhs.r > rhs.r;
    });
    std::vector<T> ans(m);
    int l = 0, r = -1;
    T cur = 0;
    for (const auto &[ql, qr, id] : q) {
        while (l > ql)
            move(--l, 1, cur);
        while (r < qr)
            move(++r, 1, cur);
        while (l < ql)
            move(l++, -1, cur);
        while (r > qr)
            move(r--, -1, cur);
        ans[id] = cur;
    }
    return ans;
}
