struct trie {
  int nex[100000][26], cnt;
  bool exist[100000];  // if this node is a end of a word

  void insert(char *s, int l) {  
    int p = 0;
    for (int i = 0; i < l; i++) {
      int c = s[i] - 'a';
      if (!nex[p][c]) nex[p][c] = ++cnt;  // if the node DNE, add it
      p = nex[p][c];
    }
    exist[p] = 1;
  }
  bool find(char *s, int l) {  
    int p = 0;
    for (int i = 0; i < l; i++) {
      int c = s[i] - 'a';
      if (!nex[p][c]) return 0;
      p = nex[p][c];
    }
    return exist[p];
  }
};