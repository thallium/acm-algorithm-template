vector<vector<int>> g;
vector<int> dep,low;//low[i] is the highest vertex can be reached by its subtree, using back-edge atmost once

vector<int> cut_vertices;
void dfs(int u,int rt){
    int csize=0;
    bool ok=0;
    for(auto v:g[u]){
        if(dep[v]==0){
            low[v]=dep[v]=dep[u]+1;
            dfs(v,rt);
            low[u]=min(low[u],low[v]);
            csize++;
            if(u!=rt&&low[v]>=dep[u]) ok=1;
        }
        low[u]=min(low[u],dep[v]);//be careful
    }
    if(u==rt&&csize>1) ok=1;
    if(ok) cut_vertices.push_back(u);
}
