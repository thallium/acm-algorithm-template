struct Trie {
  Trie * child[26];
  int nums=0;  
  Trie() {
    for(int i=0;i<26;i++) child[i]=NULL;
    nums=0;
  }
};
void insert(Trie *root, const string &s) {
  Trie* r=root;
  for(int i=0;i<s.size();i++){
    int key=s[i]-'a';
    if(r->child[key]==NULL) p->child[key]=new Trie();
    r=r->child[key];
  }
  ++r->nums;
}
bool find(Trie *root, const string &s) {
  Tree* r=root;
  for(int i=0;i<s.size();++i){
    int key=s[i]-'a';
    if(r->child[key]==NULL) return false;
    r=r->child[key];
  }
  return r->nums>0;
}
