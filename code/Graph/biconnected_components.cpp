#include <vector>
using namespace std;
int main() {
    auto biconnected_comp = [&](const vector<vector<int>> &g) {
        const int n = (int)size(g);
        int pos = 0;
        vector<int> ord(n, -1), low(n), cuts, stk;
        vector<vector<int>> comps; // components

        auto dfs = [&](auto &slf, int u, int pa) -> void {
            low[u] = ord[u] = pos++;
            stk.push_back(u);
            int cnt = 0;
            bool is_cut = false;
            for (auto v : g[u]) {
                if (v == pa)
                    continue;
                if (ord[v] == -1) {
                    cnt++;
                    slf(slf, v, u);
                    low[u] = min(low[u], low[v]);
                    if (low[v] >= ord[u]) {
                        if (u != pa || cnt > 1)
                            is_cut = true;
                        // the subtree will be disconnected if we remove
                        // vertex u, do something if needed
                        comps.emplace_back();
                        while (true) {
                            int back = stk.back();
                            stk.pop_back();
                            comps.back().push_back(back);
                            if (back == v)
                                break;
                        }
                        comps.back().push_back(u);
                    }
                } else {
                    low[u] = min(low[u], ord[v]);
                }
            }
            if (is_cut)
                cuts.push_back(u);
        };

        for (int i = 0; i < n; i++) {
            if (ord[i] == -1)
                dfs(dfs, i, i);
        }

        return comps;
    };
}
/*
 * Extension: round-square tree
 * Let c be the number of biconnected components in a graph G. The round-square
 * tree consists of n round vertices and c square vertices. Each round vertex is
 * connected to the square vertices corresponding to the biconnected components
 * that the round vertex belongs to.
 * The round-square tree is a tree with n + c vertices and n + c − 1 edges.
 *
 * Example (ABC 318G):
 * Given a graph and three vertices A, B, C. Determine if there is a simple path
 * connecting vertices A and C via vertex B.
 *
 * Solution:
 * In the round-square tree, check if there is a square vertex on the path from
 * A to C that is connected to B by an edge.
 */
