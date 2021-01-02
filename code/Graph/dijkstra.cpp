// vector<pii> pre[N];
void dijkstra(int start){
    fill(dis.begin(), dis.end(), 1e9);
    priority_queue<pii,vector<pii>,greater<pii>> q;
    dis[start]=0;
    q.push({0,start});
    while(!q.empty()){
        auto [d, u]=q.top();
        q.pop();
        if(d!=dis[u]) continue;
        for(auto [cost,v]:g[u]){
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
