template<typename T>
struct Trie {
    vector<map<T, int>> child;
    vector<bool> is_leaf;

    Trie() {
        child.resize(1);
        is_leaf.resize(1);
    }

    template<typename S>
    void insert(const S& s) {
        int p=0;
        for (auto ch : s) {
            if (!child[p].count(ch)) {
                child[p][ch]=child.size();
                child.emplace_back();
                is_leaf.emplace_back();
            }
            p=child[p][ch];
        }
        is_leaf[p]=true;
    }

    template<typename S>
        bool find(const S& s) {
            int p=0;
            for (auto ch : s) {
                if (!child[p].count(ch)) return false;
                p=child[p][ch];
            }
            return is_leaf[p];
        }
};

