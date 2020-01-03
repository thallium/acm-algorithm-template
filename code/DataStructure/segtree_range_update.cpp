#include<bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
using namespace std;
typedef long long ll;

const int N=1e6+5;
ll a[N];
struct segt{
    int l,r;
    ll val,tag;
}t[N<<2];
void build(int root,int l,int r){
    t[root].l=l;
    t[root].r=r;
    if(l==r){
        t[root].val=a[l];
        return ;
    }
    int mid=(l+r)>>1;
    build(root<<1,l,mid);
    build(root<<1|1,mid+1,r);
    t[root].val=t[root<<1].val+t[root<<1|1].val;
}
void addtag(int p,int x){
    t[p].val+=(t[p].r-t[p].l+1)*x;
    t[p].tag+=x;
}
void spread(int p){
    if(t[p].tag){
        addtag(p<<1,t[p].tag);
        addtag(p<<1|1,t[p].tag);
        t[p].tag=0;
    }
}
void update(int root,int l,int r,ll x){
    if(l<=t[root].l&&r>=t[root].r){
        t[root].val+=x*(t[root].r-t[root].l+1);
        t[root].tag+=x;
        return;
    }
    spread(root);
    int mid=(t[root].l+t[root].r)/2;
    if(l<=mid) update(root<<1,l,r,x);
    if(r>mid) update(root<<1|1,l,r,x);
    t[root].val=t[root<<1].val+t[root<<1|1].val;
}
ll q(int root,int l,int r){
    if(l<=t[root].l&&r>=t[root].r) return t[root].val;
    spread(root);
    int mid=(t[root].l+t[root].r)>>1;
    ll ans=0;
    if(l<=mid) ans+=q(root<<1,l,r);
    if(r>mid) ans+=q(root<<1|1,l,r);
    return ans;
}
