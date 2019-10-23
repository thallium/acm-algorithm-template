#include<bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
using namespace std;
typedef long long ll;

const int N=1e6+5;
ll a[N];
struct segt{
    int l,r;
    ll val,add;
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
void spread(int p){
    if(t[p].add){
        t[p*2].val+=t[p].add*(t[p<<1].r-t[p<<1].l+1);
        t[p<<1|1].val+=t[p].add*(t[p<<1|1].r-t[p<<1|1].l+1);
        t[p<<1].add+=t[p].add;
        t[p<<1|1].add+=t[p].add;
        t[p].add=0;
    }
}
void update(int root,int l,int r,ll x){
    if(l<=t[root].l&&r>=t[root].r){
        t[root].val+=x*(t[root].r-t[root].l+1);
        t[root].add+=x;
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
int main(){
    
}