/*
        Push Relabel O(n^3) implimentation using FIFO method to chose push
   vertex. This uses gapRelabel heuristic to fasten the process even further. If
   only the maxFlow value is required then the algo can be stopped as soon as
   the gap relabel method is called. However, to get the actual flow values in
   the edges, we need to let the algo terminate itself.
        This implimentation assumes zero based vertex indexing. Edges to the
   graph can be added using the addEdge method only. capacity for residual edges
   is set to be zero. To get the actual flow values iterate through the edges
   and check for flow for an edge with cap > 0.
        This implimentaion is superior over dinic's for graphs where graph is
   dense locally at some places and mostly sparse. For randomly generated
   graphs, this implimentation gives results within seconds for n = 10000 nodes,
   m = 1000000 edges.
        Code Tested on : SPOJ FASTFLOW
        @author : triveni
*/
typedef int fType;
struct edge {
    int from, to;
    fType cap, flow;
    edge(int from, int to, fType cap, fType flow = 0)
        : from(from), to(to), cap(cap), flow(flow) {}
};
struct PushRelabel {
    int N;
    vector<edge> edges;
    vector<vector<int>> G;
    vector<int> h, inQ, count;
    vector<fType> excess;
    queue<int> Q;
    PushRelabel(int N) : N(N), count(N << 1), G(N), h(N), inQ(N), excess(N) {}
    void addEdge(int from, int to, int cap) {
        G[from].push_back(edges.size());
        edges.push_back(edge(from, to, cap));
        G[to].push_back(edges.size());
        edges.push_back(edge(to, from, 0));
    }
    void enQueue(int u) {
        if (!inQ[u] && excess[u] > 0) Q.push(u), inQ[u] = true;
    }
    void Push(int edgeIdx) {
        edge &e = edges[edgeIdx];
        int toPush = min<fType>(e.cap - e.flow, excess[e.from]);
        if (toPush > 0 && h[e.from] > h[e.to]) {
            e.flow += toPush;
            excess[e.to] += toPush;
            excess[e.from] -= toPush;
            edges[edgeIdx ^ 1].flow -= toPush;
            enQueue(e.to);
        }
    }
    void Relabel(int u) {
        count[h[u]] -= 1;
        h[u] = 2 * N - 2;
        for (int i = 0; i < G[u].size(); ++i) {
            edge &e = edges[G[u][i]];
            if (e.cap > e.flow) h[u] = min(h[u], h[e.to]);
        }
        count[++h[u]] += 1;
    }
    void gapRelabel(int height) {
        for (int u = 0; u < N; ++u)
            if (h[u] >= height && h[u] < N) {
                count[h[u]] -= 1;
                count[h[u] = N] += 1;
                enQueue(u);
            }
    }
    void Discharge(int u) {
        for (int i = 0; excess[u] > 0 && i < G[u].size(); ++i) {
            Push(G[u][i]);
        }
        if (excess[u] > 0) {
            if (h[u] < N && count[h[u]] < 2) gapRelabel(h[u]);
            else
                Relabel(u);
        } else if (!Q.empty()) { // dequeue
            Q.pop();
            inQ[u] = false;
        }
    }
    fType getFlow(int src, int snk) {
        h[src] = N;
        inQ[src] = inQ[snk] = true;
        count[0] = N - (count[N] = 1);
        for (int i = 0; i < G[src].size(); ++i) {
            excess[src] += edges[G[src][i]].cap;
            Push(G[src][i]);
        }
        while (!Q.empty()) {
            Discharge(Q.front());
        }
        return excess[snk];
    }
};
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    PushRelabel df(n);
    while (m--) {
        int x, y, c;
        // cin >> x >> y >> c; // 0- based index
        scanf("%d%d%d", &x, &y, &c);
        --x, --y;
        if (x != y) {
            df.addEdge(x, y, c);
            df.addEdge(y, x, c);
        }
    }
    cout << df.getFlow(0, n - 1) << "\n";
    return 0;
}
