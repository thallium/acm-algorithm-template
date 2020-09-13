mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
struct Treap{
    struct data{
        int v;
        bool operator == (const data& d) const {
            return v==d.v;
        }
        bool operator < (const data& d) const {
            return v<d.v;
        }
    };
    struct node{
        int ch[2],sz,dup;
        unsigned k;
        data d;
        node(int z=1):sz(z),dup(z),k(gen()){
            ch[0]=ch[1]=0;
        }
    };
    vector<node> nodes;
    vector<int> recycle;
    int root,reserve_size;
    Treap(int size=0){
        nodes.clear();
        recycle.clear();
        nodes.reserve(size+1);
        nodes.push_back(node(0));
        root=0;
        reserve_size=size+1;
    }
    void reserve(){
        if(size()>=reserve_size) nodes.reserve((reserve_size*=2)+1);
    }
    int new_node(){
        int id=nodes.size();
        if(!recycle.empty()){
            id=recycle.back();
            recycle.pop_back();
            nodes[id]=node();
        }else nodes.push_back(node());
        return id;
    }
    void update(int rt){
        node& n=nodes[rt];
        n.sz=n.dup+nodes[n.ch[0]].sz+nodes[n.ch[1]].sz;
    }
    int insert(int& rt, data& d){// insert a data in bst rooted at rt
        if(rt==0){
            rt=new_node();
            nodes[rt].d=d;
            return rt;
        }
        node& cur=nodes[rt];
        cur.sz++;
        if(d==cur.d){
            cur.dup++;
            return rt;
        }
        //changed
        bool r=cur.d<d;
        int& s=cur.ch[r];
        int ret=insert(s,d);
        if(nodes[s].k<cur.k) rotate(rt,r),update(rt);
        return ret;
    }
    void rotate(int& rt,int r){
        node& cur=nodes[rt];
        int s=cur.ch[r];
        cur.ch[r]=nodes[s].ch[r^1];
        nodes[s].ch[r^1]=rt;
        update(rt);
        rt=s;
    }
    int find(int& rt,const data& d){
        if(rt==0) return 0;
        if(d==nodes[rt].d) return rt;
        //changed
        return find(nodes[rt].ch[(nodes[rt].d<d)],d);
    }
    bool erase_founded(int& rt,const data& d){//returns if founded
        if(rt==0) return false;
        if(d==nodes[rt].d){
            nodes[rt].sz--;
            if(--nodes[rt].dup<=0) remove(rt);
            return true;
        }
        //changed
        if(erase_founded(nodes[rt].ch[(nodes[rt].d<d)],d)){
            nodes[rt].sz--;
            return true;
        }
        return false;
    }
    void remove(int& rt){
        if(rt==0) return;
        if(!nodes[rt].ch[0] || !nodes[rt].ch[1]){ // if one child is empty
            recycle.push_back(rt);
            rt=nodes[rt].ch[!nodes[rt].ch[0]];
        }else{
            int r=nodes[nodes[rt].ch[0]].k<nodes[nodes[rt].ch[1]].k;
            rotate(rt,r^1);
            remove(nodes[rt].ch[r]);
            update(rt);
        }
    }
    int kth(int rt,int k){
        node& cur=nodes[rt];
        int sz=nodes[cur.ch[0]].sz;
        if(sz>=k) return kth(cur.ch[0],k);
        if(sz+cur.dup>=k) return rt;
        return kth(cur.ch[1],k-sz-cur.dup);
    }
    int rank(int rt,const data& d,bool count_dup){
        if(rt==0) return 1;
        node& cur=nodes[rt];
        if(d==cur.d) return nodes[cur.ch[0]].sz+1+count_dup*cur.dup;
        if(d<cur.d) return rank(cur.ch[0],d,count_dup);
        return rank(cur.ch[1],d,count_dup)+nodes[cur.ch[0]].sz+cur.dup;
    }
    //interface
    int get(int id){ return nodes[id].d.v; }
    int size(){ return nodes[root].sz;}
    int insert(data v){ reserve(); return insert(root,v);}
    bool erase(data v){ return erase_founded(root,v);}
    int find(data v){ return find(root,v);}//return id;
    int find_by_order(int k){ return get(kth(root,k));}
    int order_of_key(data v,bool count_dup=0){ return rank(root,v,count_dup);}
};
int main(){
    tr.find_by_order(tr.order_of_key({x})-1);//first element smaller than x
    tr.find_by_order(tr.order_of_key({x},true));//upper_bound(x)
}
