#include<bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define ms(a,x) memset(a,x,sizeof(a))
#define tr t[root]
using namespace std;

const int N=5e4+5;
struct segtree{
    int l,r,val;
}t[N<<2];
int a[N];
void build(int root,int l,int r){
    tr.l=l;
    tr.r=r;
    if(l==r){
        tr.val=a[l];
        return;
    }
    int mid=(l+r)>>1;
    build(root<<1,l,mid);
    build(root<<1|1,mid+1,r);
    tr.val=t[root<<1].val+t[root<<1|1].val;
}
void update(int root,int i,int x){
    int l=tr.l;
    int r=tr.r;
    if(tr.l==tr.r){
        tr.val+=x;
        return;
    }
    int mid=(l+r)/2;
    if(i<=mid) update(root<<1,i,x);
    else update(root<<1|1,i,x);
    tr.val=t[root<<1].val+t[root<<1|1].val;
}
int q(int root,int l,int r){
    if(l<=tr.l&&r>=tr.r){
        return tr.val;
    }
    int mid=(tr.l+tr.r)>>1;
    int ans=0;
    if(l<=mid) ans+=q(root<<1,l,r);
    if(r>mid) ans+=q(root<<1|1,l,r);
    return ans;
}