// suppose you have some boolean variables a, b, c, d...
// assign each variable true or false such that the expression like
// the following is true:
// (a or not b) and (not a or b) and (not a or not b) and (a or not c)
// the expression is a conjunction of multiple clauses, where each clause
// is a disjunction of exactly two literals

#include <bits/stdc++.h>
#include <Graph/tarjan_SCC.cpp>
using namespace std;

struct two_SAT {
    int n;
    SCC g;
    two_SAT(int n) : n(n), g(n*2) {} // n is the number of literals
    void add(int u, bool neg_u, int v, bool neg_v) { // neg_u is if u is negated, same for v
        g.add_edge(2*u+neg_u, 2*v+!neg_v);
        g.add_edge(2*v+neg_v, 2*u+!neg_u);
    }

    vector<bool> solve() {
        g.solve();
        de(g.color);
        vector<bool> res(n);
        for (int i=0; i<n; i++) {
            if (g.color[2*i]==g.color[2*i+1]) return {};
            res[i]=g.color[2*i]>g.color[2*i+1];
        }
        return res;
    }
};
