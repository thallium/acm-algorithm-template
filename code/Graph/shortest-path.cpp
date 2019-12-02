const int N=2e5+5;
vector<pii> E[N];
int dis[N];
bool vis[N];
// vector<pii> pre[N];
void dijkstra(int start){
	ms(vis,false);
	ms(dis,INF);
	priority_queue<pii,vector<pii>,greater<pii>> q;
	dis[start]=0;
	q.push({0,start});
	while(!q.empty()){
		pii tmp=q.top();
		q.pop();
		int u=tmp.S;
		if(vis[u]) continue;
		vis[u]=1;
		for(pii it:E[u]){
			ll v=it.S,cost=it.F;
			if(!vis[v]&&dis[v]>dis[u]+cost){
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
