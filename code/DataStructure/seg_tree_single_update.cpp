struct SegTree{
    int n;
    vector<int> t;
    SegTree(int n_):n(n_),t(4*n){}
    SegTree(const vector<int>& v):SegTree((int)v.size()){
        build(1,0,n-1,v);
    }
    void pushup(int node){
        t[node]=t[node<<1]+t[node<<1|1];
    }
    void build(int node,int l,int r,const vector<int>& v){
        if(l==r){
            t[node]=v[l];
            return;
        }
        int mid=(l+r)>>1;
        build(root<<1,l,mid,v);
        build(root<<1|1,mid+1,r,v);
        pushup(node);
    }
    void update(int node,int i,int x,int l,int r){
        if(l==r){
            t[node]+=x;
            return;
        }
        int mid=(l+r)/2;
        if(i<=mid) update(node<<1,i,x,l,mid);
        else update(node<<1|1,i,x,mid+1,r);
        pushup(node);
    }
    int query(int node,int ql,int qr,int l,int r){
        if(ql<=l&&qr>=r){
            return t[node];
        }
        int mid=(l+r)>>1;
        int ans=0;
        if(ql<=mid) ans+=query(node<<1,ql,qr,l,mid);
        if(qr>mid) ans+=query(node<<1|1,ql,qr,mid+1,r);
        return ans;
    }
};
