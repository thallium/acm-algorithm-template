#pragma once
// Hopcroft–Karp algorithm

#include <vector>
#include <array>
#include "graph/dinic.hpp"

// Finds the maximum-carinality matching of a bipartite graph in O(E sqrt(V)) time in worst case.
// In the case of dense graph the time bound becomes O(V ^ 2.5) and for sparse random graph it runs
// in O(E log V) with high probablity.
//
// Tested on https://judge.yosupo.jp/problem/bipartitematching
template<typename T>
static auto hopcroft_karp(const std::vector<T>& edges, int n, int m) -> std::vector<std::array<int, 2>> {
    Dinic flow(n + m + 2);
    const int source = n + m, sink = n + m + 1;

    for (auto [u, v] : edges) {
        flow.addEdge(u, v + n, 1);
    }
    for (int i = 0; i < n; i++) {
        flow.addEdge(source, i, 1);
    }
    for (int i = n; i < n + m; i++) {
        flow.addEdge(i, sink, 1);
    }

    flow.maxFlow(source, sink);

    std::vector<std::array<int, 2>> matching;

    int i = 0;
    for (auto [u, v] : edges) {
        if (flow.e[i * 2].cap == 0) {
            matching.push_back({u, v});
        }
        i++;
    }
    return matching;
}
