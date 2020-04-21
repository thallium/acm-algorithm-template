struct Trie {
    int child[100000][26], cnt=0;
    bool exist[100000];  // if this node is a end of a word

    void insert(string s) {  
        int len=s.size();
        int p = 0;
        for (int i = 0; i < len; i++) {
            int c = s[i] - 'a';
            if (!child[p][c]) child[p][c] = ++cnt;  // if the node DNE, add it
            p = child[p][c];
        }
        exist[p] = 1;
    }
    bool find(string s) {  
        int len=s.size();
        int p = 0;
        for (int i = 0; i < len; i++) {
            int c = s[i] - 'a';
            if (!child[p][c]) return 0;
            p = child[p][c];
        }
        return exist[p];
    }
};
