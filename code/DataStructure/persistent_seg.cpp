//find the nth biggest number
const int N=1e5+5;
struct node{
    int l,r,val;
};
int ver[N];
node tr[N*20];
int cnt=0;
void build(int& rt,int l,int r){
    rt=++cnt;
    tr[rt].val=0;
    if(l==r) return;
    int mid=(l+r)>>1;
    build(tr[rt].l,l,mid);
    build(tr[rt].r,mid+1,r);
}
void update(int& rt,int l,int r,int val){
    tr[++cnt]=tr[rt];
    rt=cnt;
    tr[rt].val++;
    if(l==r) return;
    int mid=(l+r)>>1;
    if(val<=mid) update(tr[rt].l,l,mid,val);
    else update(tr[rt].r,mid+1,r,val);
}
int query(int rl,int rr,int l,int r,int val){
    int d=tr[tr[rr].r].val-tr[tr[rl].r].val;
    if(l==r) return l;
    int mid=(l+r)>>1;
    if(val<=d) return query(tr[rl].r,tr[rr].r,mid+1,r,val);
    else return query(tr[rl].l,tr[rr].l,l,mid,val-d);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	cnt=0;
	build(ver[0],1,len);
    forn(i,n){
		int x;
		cin>>x;
		int pos=getpos(x);
		update(ver[i],1,len,pos);
	}
	query(ver[l-1],ver[r],1,len,kth);
}