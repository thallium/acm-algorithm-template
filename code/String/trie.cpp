#include <bits/stdc++.h>
using namespace std;
template <typename T> struct Trie {
    struct node {
        map<T, int> ch;
        bool is_leaf;
    };
    vector<node> t;
    Trie() { new_node(); }
    int new_node() {
        t.emplace_back();
        return (int)t.size() - 1;
    }
    template <typename S> void insert(const S &s) {
        int p = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            auto ch = s[i];
            if (!t[p].ch.count(ch)) {
                t[p].ch[ch] = new_node();
            }
            p = t[p].ch[ch];
        }
        t[p].is_leaf = true;
    }
    template <typename S> bool find(const S &s) {
        int p = 0;
        for (auto ch : s) {
            if (!t[p].ch.count(ch))
                return false;
            p = t[p].ch[ch];
        }
        return t[p].is_leaf;
    }
};
