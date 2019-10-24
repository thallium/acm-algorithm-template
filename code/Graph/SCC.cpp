#include<bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;
typedef long long ll;

int n,m;
const int N=1e4+5;
vector<int> vec[N];//graph
int id=1,scc=0;
int ids[N],low[N];//vevrtices with same low value are in the same SCC
bool onstack[N];
int stk[N],top=-1;
int out[N];
void dfs(int x){
    stk[++top]=x;
    onstack[x]=1;
    ids[x]=low[x]=id++;
    forn(i,vec[x].size()){
        int to=vec[x][i];
        if(ids[to]==-1) dfs(to);
        if(onstack[to]) low[x]=min(low[to],low[x]);
    }
    if(ids[x]==low[x]){
        while(top>-1){
            int node=stk[top--];
            onstack[node]=0;
            low[node]=ids[x];
            if(node==x) break;
        }
        scc++;
    }
}
void tarjan(){
    for1(i,n) ids[i]=-1;
    for1(i,n){
        if(ids[i]==-1) dfs(i);
    }
}
