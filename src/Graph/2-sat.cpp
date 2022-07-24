// suppose you have some boolean variables a, b, c, d...
// assign each variable true or false such that the expression like
// the following is true:
// (a or not b) and (not a or b) and (not a or not b) and (a or not c)
// the expression is a conjunction of multiple clauses, where each
// clause is a disjunction of exactly two literals

#include "graph/tarjan_scc.hpp"
#include <vector>

struct TwoSAT {
    int n;
    std::vector<std::vector<int>> g;
    TwoSAT(int n) : n(n), g(n * 2) {} // n is the number of literals

    void add(int u, bool neg_u, int v, bool neg_v) { // neg_u is if u is negated, same for v
        g[2 * u + neg_u].push_back(2 * v + !neg_v);
        g[2 * v + neg_v].push_back(2 * u + !neg_u);
    }

    std::vector<bool> solve() {
        auto [cnt, color] = scc(g);

        std::vector<bool> res(n);
        for (int i = 0; i < n; i++) {
            if (color[2 * i] == color[2 * i + 1]) return {};
            res[i] = color[2 * i] > color[2 * i + 1];
        }
        return res;
    }
};
