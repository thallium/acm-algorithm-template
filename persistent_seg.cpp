//find the nth biggest in [l,r]
#include<bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
using namespace std;

typedef long long ll;
#define lson tree[tree[root].l]
#define rson tree[tree[root].r]
#define tr tree[root]
#define tcur tree[cur]
const int maxn=1e5+5;
const int mxsz=(maxn*20)+10;
int tot=0;
int a[maxn],ver[maxn];
struct segtree{
	int l,r,data;
}tree[mxsz];
void build(int l,int r,int root){
	if(l==r){
		tr.data=0;
		return;
	}
	int mid=(l+r)>>1;
	tree[root].l=++tot;
	build(l,mid,tr.l);
	tree[root].r=++tot;
	build(mid+1,r,tr.r);
	tree[root].data=lson.data+rson.data;
}
void update(int root,int cur,int l,int r,int id){
	if(l==r) return;
	int mid=(l+r)>>1;
	if(id<=mid){
		tcur.r=tr.r;
		tcur.l=++tot;
		update(tr.l,tcur.l,l,mid,id);
	}else{
		tcur.l=tr.l;
		tcur.r=++tot;
		update(tr.r,tcur.r,mid+1,r,id);
	}
	tcur.data=tree[tcur.l].data+tree[tcur.r].data;
}
int query(int o,int v,int l,int r,int kth){
	if(l==r) return l;
	int mid=(l+r)>>1;
	int res=tree[tree[v].l].data-tree[tree[o].l].data;
	if(res>=kth)  return query(tree[o].l,tree[v].l,l,mid,kth);
	else return query(tree[o].r,tree[v].r,mid+1,r,kth-res);
}
int n,m,idx[maxn];
int main(){    
	update(ver[i-1],ver[i],1,len,x);
	query(ver[l-1],ver[r],1,len,k)];
}
