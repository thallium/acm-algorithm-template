template<typename T>
struct Trie {
    vector<map<T, int>> child;
    vector<bool> is_leaf;
    Trie() { new_node(); }
    int new_node() {
        child.emplace_back();
        is_leaf.emplace_back();
        return child.size()-1;
    }
    template<typename S> void insert(const S& s) {
        int p=0;
        for (auto ch : s) {
            if (!child[p].count(ch)) {
                child[p][ch]=new_node();
            }
            p=child[p][ch];
        }
        is_leaf[p]=true;
    }
    template<typename S> bool find(const S& s) {
        int p=0;
        for (auto ch : s) {
            if (!child[p].count(ch)) return false;
            p=child[p][ch];
        }
        return is_leaf[p];
    }
};
