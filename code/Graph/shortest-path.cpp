const int N=2e5+5;
vector<pii> G[N];
int dis[N];
// vector<pii> pre[N];
void dijkstra(int start){
    ms(dis,INF);
    priority_queue<pii,vector<pii>,greater<pii>> q;
    dis[start]=0;
    q.push({0,start});
    while(!q.empty()){
        pii tmp=q.top();
        q.pop();
        int u=tmp.S;
        if(tmp.F!=dis[u]) continue;
        for(auto [cost,v]:G[u]){
            if(dis[v]>dis[u]+cost){
                dis[v]=dis[u]+cost;
                // pre[v].clear();
                // pre[v].pb({cost,u});
                q.push({dis[v],v});
            }
            // else if(dis[v]==dis[u]+cost)
            // 	pre[v].pb({cost,u});
        }
    }
}
