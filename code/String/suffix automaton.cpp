// source: https://cp-algorithms.com/string/suffix-automaton.html
struct SAM {
    struct state {
        int len = 0, link = -1;
        unordered_map<char, int> next;
    };
    int last = 0; // the index of the equivalence class of the whole string
    vector<state> st;
    void extend(char c) {
        int cur = (int)st.size();
        st.emplace_back();
        st[cur].len = st[last].len + 1;
        int p = last;
        while (p != -1 && !st[p].next.count(c)) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) st[cur].link = 0;
        else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = (int)st.size();
                st.push_back(st[q]);
                st[clone].len = st[p].len + 1;
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }
    SAM() { st.emplace_back(); }
    SAM(const string &s) : SAM() {
        for (auto c : s)
            extend(c);
    }
};
