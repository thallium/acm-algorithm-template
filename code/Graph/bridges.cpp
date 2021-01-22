int n; 
VVI adj;
VI visited;
VI tin, low;
int timer;

void dfs(int v, int p=-1){
  visited[v]=1;
  tin[v]=low[v]=timer++;
  int children=0;
  for(auto &to : adj[v]) {
    if(to==p) continue;
    if(visited[to]) {
      low[v]=min(low[v],tin[to]);
    }
    else{
      dfs(to,v);
      low[v]=min(low[v],low[to]);
      if(low[to] >= tin[v] && p!=-1) IS_CUTPOINT(v);
      if(low[to] > tin[v]) IS_BRIDGE(v,to);
      ++children;
    }
  }
  if(p==-1 && children>1)  IS_CUTPOINT(v);
}

void find_bridges() {
  timer=0; visited.assign(n,0);
  tin.assign(n,-1);
  low.assign(n,-1);
  FOR(i,n){
    if(!visited[i]) dfs(i);
  }
}
