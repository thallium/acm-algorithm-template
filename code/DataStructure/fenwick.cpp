#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct fenwick{
    int n;
    vector<T> t;

    fenwick(int n_):n(n_), t(n+1) {}
    fenwick(const vector<int>& v) : fenwick((int)v.size()) { 
        for (int i=1;i<=n;i++) {
            t[i]+=v[i-1]; int j=i+(i&-i); if(j<=n) t[j]+=t[i];
        }
    }

    void update(int i,int x){
        for(;i<=n;i+=i&-i){
            t[i]+=x;
        }
    }

    T query(int i){
        T res=0;
        for(;i>0;i-=i&-i) res+=t[i];
        return res;
    }

    T query(int l,int r){
        return query(r)-query(l-1);
    }
    int search(T prefix){//equivalent to upper_bound(prefix)
        int pos=0;
        T sum=0;
        for(int i=20;i>=0;i--){
            if(pos+(1<<i)<=n&&(sum+t[pos+(1<<i)]<=prefix)){
                pos+=(1<<i);
                sum+=t[pos];
            }
        }
        return pos+1;
    }
};

//fenwick tree with range update and range sum query
struct fenwick{
    int n;
    vector<ll> sum1,sum2;
    fenwick(int n_):n(n_),sum1(n),sum2(n){}

    void update(int p, ll x){
        for(int i=p;i<=n;i+=i&-i) sum1[i] += x, sum2[i] += x * p;
    }
    void update(int l,int r, ll x){
        update(l, x), update(r + 1, -x);
    }
    ll query(int p){
        ll res = 0;
        for(int i=p;i;i-=i&-i) res += (p + 1) * sum1[i] - sum2[i];
        return res;
    }
    ll query(int l,int r){
        return query(r)-query(l-1);
    }
};
// two dimensional, single update, range query
struct fenwick{
    int n;
    vector<vector<int>> tree;
    fenwick(int n_)tree(n+1,vector<int>(n+1)){}
    void add(int x, int y, int z){ 
        int memo_y = y;
        while(x <= n){
            y = memo_y;
            while(y <= n) tree[x][y] += z, y += y & -y;
            x += x & -x;
        }
    }
    void ask(int x, int y){
        int res = 0, memo_y = y;
        while(x){
            y = memo_y;
            while(y)
                res += tree[x][y], y -= y & -y;
            x -= x & -x;
        }
    }
};
// 2D, range update, single query
struct fenwick{
    void add(int x, int y, int z){ 
        int memo_y = y;
        while(x <= n){
            y = memo_y;
            while(y <= n)
                tree[x][y] += z, y += y & -y;
            x += x & -x;
        }
    }
    void range_add(int xa, int ya, int xb, int yb, int z){
        add(xa, ya, z);
        add(xa, yb + 1, -z);
        add(xb + 1, ya, -z);
        add(xb + 1, yb + 1, z);
    }
    void ask(int x, int y){
        int res = 0, memo_y = y;
        while(x){
            y = memo_y;
            while(y)
                res += tree[x][y], y -= y & -y;
            x -= x & -x;
        }
    }
};
// 2D, range update, range query
struct fenwick{
    ll t1[N][N], t2[N][N], t3[N][N], t4[N][N];
    void add(ll x, ll y, ll z){
        for(int X = x; X <= n; X += X & -X)
            for(int Y = y; Y <= m; Y += Y & -Y){
                t1[X][Y] += z;
                t2[X][Y] += z * x;
                t3[X][Y] += z * y;
                t4[X][Y] += z * x * y;
            }
    }
    void range_add(ll xa, ll ya, ll xb, ll yb, ll z){ //(xa, ya) 到 (xb, yb) 的矩形
        add(xa, ya, z);
        add(xa, yb + 1, -z);
        add(xb + 1, ya, -z);
        add(xb + 1, yb + 1, z);
    }
    ll ask(ll x, ll y){
        ll res = 0;
        for(int i = x; i; i -= i & -i)
            for(int j = y; j; j -= j & -j)
                res += (x + 1) * (y + 1) * t1[i][j]
                    - (y + 1) * t2[i][j]
                    - (x + 1) * t3[i][j]
                    + t4[i][j];
        return res;
    }
    ll range_ask(ll xa, ll ya, ll xb, ll yb){
        return ask(xb, yb) - ask(xb, ya - 1) - ask(xa - 1, yb) + ask(xa - 1, ya - 1);
    }
};
