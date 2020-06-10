vector<int> G[N];
vector<int> fa,dep,heavy,head,pos,posr;//initialize heavy with -1
int cnt;
int dfs(int u){
	int size=1;
	int mx=0;
	for(int v:G[u]){
		if(v!=fa[u]){
			fa[v]=u,dep[v]=dep[u]+1;
			int csize=dfs(v);
			size+=csize;
			if(csize>mx) mx=csize, heavy[u]=v;
		}
	}
	return size;
}
void dfs2(int u,int h){
	head[u]=h,pos[u]=++cnt;
	if(heavy[u]!=-1) dfs2(heavy[u],h);
	for(int v:G[u]){
		if(v!=fa[u]&&v!=heavy[u]) dfs2(v,v);
	}
	posr[u]=cnt;
}
ll pathsum(int u,int v){
    ll res=0;
    while(head[u]!=head[v]){
        if(dep[head[u]]<dep[head[v]]) swap(u,v);
        res+=interval_sum(pos[head[u]],pos[u]);
        u=fa[head[u]];
    }
    if(pos[u]>pos[v]) swap(u,v);
    res+=interval_sum(pos[u],pos[v]);
    return res;
}
