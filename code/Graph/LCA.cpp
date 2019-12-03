const int N=2e5+5;
vector<int> G[N];
int dep[N],fa[N][31];

void dfs(int root,int f){
  fa[root][0]=f;
  dep[root]=dep[f]+1;
  for1(i,30){
    fa[root][i]=fa[fa[root][i-1]][i-1];
  }
  for(auto it:G[root]){
    if(it==f) continue;
    dfs(it,root);
  }
}

int lca(int x,int y){
  if(dep[x]>dep[y]) swap(x,y);
  int tmp=dep[y]-dep[x];
  for(int j=0;tmp;++j, tmp>>=1){
    if(tmp&1) y=fa[y][j];
  }
  if(x==y) return x;
  for(int j=30;j>=0&&y!=x;--j){
    if(fa[x][j]!=fa[y][j]){
      x=fa[x][j];
      y=fa[y][j];
    }
  }
  return fa[x][0];
}
