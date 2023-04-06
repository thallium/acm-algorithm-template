#include <vector>

struct HamiltonianCycle {
    int n;
    std::vector<std::vector<int>> g;
    std::vector<int> dp, incident;

    HamiltonianCycle(int _n, std::vector<std::vector<int>> _g)
        : n(_n), g(_g), dp(1 << n), incident(n) {
        assert(g.size() == n);
        for (int i = 0; i < n; i++) {
            assert(g[i].size() == n);
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                incident[i] |= g[i][j] << j;
            }
        }
        for (int msk = 1; msk < (1 << n); msk++) {
            for (int b = __builtin_ctz(msk) + 1; b < n; b++) {
                if (msk >> b & 1) {
                    dp[msk] |= bool(dp[msk ^ (1 << b)] & incident[b]) << b;
                }
            }
        }
    }

    bool has_cycle(int mask) {
        assert(mask >= 0 && mask < (1 << n));
        return dp[mask] & incident[__builtin_ctz(mask)];
    }

    bool has_cycle() {
        return has_cycle((1 << n) - 1);
    }

    std::vector<int> find_cycle(int mask) {
        assert(mask >= 0 && mask < (1 << n));
        int fi = __builtin_ctz(mask);
        if (!dp[mask] || ((dp[mask] & incident[fi]) == 0)) return {};

        int next = fi;
        std::vector<int> path;
        while (mask) {
            int i = __builtin_ctz(dp[mask] & incident[next]);
            path.push_back(i);
            mask ^= (1 << i);
            next = i;
        }

        return path;
    }
};
