// finds the maximum clique in O(2 ^ (n / 2)), where n is the number of vertices.
// We force a self-loop on each vertex in a clique so you can use it to find min
// vertex cover/max independent set in a graph with self-loops.
#include <vector>
#include <map>

static long long max_clique(const std::vector<long long>& g, const std::vector<int>& cost) {
    int n = (int)size(g);

    std::map<long long, long long> memo{{0, 0}};
    auto solve = [&](auto& slf, long long mask) {
        if (memo.count(mask)) {
            return memo[mask];
        }
        int first = __builtin_ctzll(mask);
        return memo[mask] = std::max(slf(slf, mask ^ (1LL << first)), 
                g[first] >> first & 1 ? slf(slf, (mask & g[first]) ^ 1LL << first) + cost[first] : 0);
    };
    return solve(solve, (1LL << n) - 1);
}
