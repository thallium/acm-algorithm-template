vector<vector<pair<int, int>>> g;
vector<int> query, subtreeSize, parent;
vector<bool> blocked;
// calculate substree size
void calSize(int u, int p) {
    parent[u] = p;
    subtreeSize[u] = 1;
    for (auto [v, w] : g[u]) {
        if (v == p || blocked[v]) continue;
        calSize(v, u);
        subtreeSize[u] += subtreeSize[v];
    }
}
// if needed solveTree can return value
void solveTree(int root) {
    queue<pii> cur; // store the result for current subtree
    for (auto [v, w] : g[root]) {
        if (blocked[v]) continue;
        queue<pair<int, int>> q; // change if type of element if needed
        q.push({v, w});
        while (!q.empty()) {
            auto [u, dis] = q.front();
            q.pop();
            // do ... to update answer
            cur.push({dis, len});
            for (auto [to, wei] : g[u]) {
                if (to == parent[u] || blocked[to]) continue;
                q.push({to, dis + wei});
            }
        }
        while (!cur.empty()) {
            auto [dis, len] = cur.front();
            // do ... to update the result for the current tree
            cur.pop();
        }
    }
}
// return some value if needed
void go(int entry) {
    calSize(entry, entry);
    int centroid = entry;
    int bestSize = subtreeSize[entry];
    queue<int> q;
    q.push(entry);
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        int size = subtreeSize[entry] - subtreeSize[u];
        for (auto [v, w] : g[u]) {
            if (v == parent[u] || blocked[v]) continue;
            size = max(size, subtreeSize[v]);
            q.push(v);
        }
        if (size < bestSize) centroid = u, bestSize = size;
    }
    calSize(centroid, centroid);
    blocked[centroid] = true;
    // do ... to clear the previous result
    solveTree(centroid);
    for (auto [v, w] : g[centroid]) {
        if (!blocked[v]) go(v);
    }
}
