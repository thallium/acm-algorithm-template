#include <unordered_map>
#include <vector>
template <typename T> struct Trie {
    struct node {
        std::unordered_map<T, int> child;
        bool is_leaf;
    };

    std::vector<node> t;

    Trie() { new_node(); }

    int new_node() {
        t.emplace_back();
        return (int)t.size() - 1;
    }

    template <typename S> void insert(const S &s) {
        int p = 0;
        for (const auto &c : s) {
            if (!t[p].child.count(c)) {
                t[p].child[c] = new_node();
            }
            p = t[p].child[c];
        }
        t[p].is_leaf = true;
    }

    template <typename S> bool find(const S &s) {
        int p = 0;
        for (auto ch : s) {
            if (!t[p].child.count(ch)) {
                return false;
            }
            p = t[p].child[ch];
        }
        return t[p].is_leaf;
    }
};
