struct Trie {
    int child[100000][26], cnt=0;
    bool leaf[100000];  // if this node is a end of a word

    void insert(string s) {  
        int p = 0;
        for(auto ch:s){
            int c = ch - 'a';
            if (!child[p][c]) child[p][c] = ++cnt;  // if the node DNE, add it
            p = child[p][c];
        }
        leaf[p] = 1;
    }
    bool find(string s) {  
        int p = 0;
        for(auto ch:s){
            int c = ch - 'a';
            if (!child[p][c]) return 0;
            p = child[p][c];
        }
        return leaf[p];
    }
};

struct Trie{
    array<unique_ptr<Trie>, 26> child;
    bool isleaf=0,checked=0;
    void insert(string s){
        auto p=this;
        for(auto ch:s){
            int x=ch-'a';
            if(p->child[x]==nullptr) p->child[x]= make_unique<Trie>();
            p=p->child[x].get();
        }
        p->isleaf=true;
    }
    int find(string s){
        auto p=this;
        for(auto ch:s){
            int x=ch-'a';
            if(p->child[x]==nullptr) return -1;
            p=p->child[x].get();
        }
        if(p->checked) return 0;
        else {
            p->checked=1;
            return 1;
        }
    }
};

