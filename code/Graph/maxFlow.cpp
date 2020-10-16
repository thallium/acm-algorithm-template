// indexed from 0!
struct Dinic {
    struct Edge {
        int from, to, cap, flow;
        Edge(int u, int v, int c, int f) : from(u), to(v), cap(c), flow(f) {}
    };
    int n, s, t;
    vector<Edge> edges;
    vector<vector<int>> g;
    vector<int> d,cur;
    vector<int> vis;

    Dinic(int _n) : n(_n), g(n), d(n), cur(n), vis(n){
        edges.clear();
    }

    void init(int n) {
        for (int i = 0; i < n; i++) g[i].clear();
        edges.clear();
    }

    void AddEdge(int from, int to, int cap) {
        edges.push_back(Edge(from, to, cap, 0));
        edges.push_back(Edge(to, from, 0, 0));
        int m = (int) edges.size();
        g[from].push_back(m - 2);
        g[to].push_back(m - 1);
    }

    bool BFS() {
        fill(vis.begin(), vis.end(), 0);
        queue<int> Q;
        Q.push(s);
        d[s] = 0;
        vis[s] = 1;
        while (!Q.empty()) {
            int x = Q.front();
            Q.pop();
            for (int i = 0; i < (int) g[x].size(); i++) {
                Edge& e = edges[g[x][i]];
                if (!vis[e.to] && e.cap > e.flow) {
                    vis[e.to] = 1;
                    d[e.to] = d[x] + 1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }

    int DFS(int x, int a) {
        if (x == t || a == 0) return a;
        int flow = 0, f;
        for (int& i = cur[x]; i < (int) g[x].size(); i++) {
            Edge& e = edges[g[x][i]];
            if (d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap - e.flow))) > 0) {
                e.flow += f;
                edges[g[x][i] ^ 1].flow -= f;
                flow += f;
                a -= f;
                if (a == 0) break;
            }
        }
        return flow;
    }

    int Maxflow(int s, int t) {
        this->s = s;
        this->t = t;
        int flow = 0;
        while (BFS()) {
            const int INF=1e9;
            fill(cur.begin(), cur.end(), 0);
            flow += DFS(s, INF);
        }
        return flow;
    }
};
