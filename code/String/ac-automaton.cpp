/**
 * Modified from:
 * https://github.com/kth-competitive-programming/kactl/blob/master/content/strings/AhoCorasick.h
 * Description: Aho-Corasick automaton, used for multiple pattern matching.
 * The automaton start node will be at index 0. find(word) returns for each
 * position the index of the longest word that ends there, or -1 if none.
 * Try to handdle duplicated patterns beforehand, otherwise change 'end' to
 * vector; empty patterns are not allowed. For large alphabets, split each
 * symbol into chunks, with sentinel bits for symbol boundaries. Time:
 * construction takes $O(26N)$, where $N =$ sum of length of patterns. find(x)
 * is $O(N)$, where N = length of x. findAll is $O(N+M)$ where M is number of
 * occurrence of all pattern (up to N*sqrt(N))
 */
#include <bits/stdc++.h>
using namespace std;

struct AhoCorasick {
    enum { alpha = 26, first = 'a' }; // change this!
    struct Node {
        // (nmatches is optional)
        // back: failure link, points to longest suffix that is in the trie
        // end: longest pattern that ends here, is -1 if no patten ends here
        // nmatches: number of (patterns that is a suffix of current
        // node)/(duplicated patterns), depends on needs output: output link,
        // points to the longest pattern that is a suffix of current node
        int back, end = -1, nmatches = 0, output = -1;
        array<int, alpha> next;
        Node(int v = -1) { fill(next.begin(), next.end(), v); }
    };
    vector<Node> N;

    AhoCorasick() : N(1) {}

    void insert(string &s, int j) { // j: id of string s
        assert(!s.empty());
        int n = 0;
        for (char c : s) {
            int &m = N[n].next[c - first];
            if (m == -1) {
                m = (int)N.size();
                N.emplace_back();
            }
            n = m;
        }
        N[n].end = j;
        N[n].nmatches++;
    }

    void build() {
        N[0].back = (int)N.size();
        N.emplace_back(0);

        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int n = q.front();
            q.pop();
            for (int i = 0; i < alpha; i++) {
                int pnx = N[N[n].back].next[i];
                auto &nxt = N[N[n].next[i]];
                if (N[n].next[i] == -1) N[n].next[i] = pnx;
                else {
                    nxt.back = pnx;
                    // if prev is an end node, then set output to prev node,
                    // otherwise set to output link of prev node
                    nxt.output = N[pnx].end == -1 ? N[pnx].output : pnx;
                    // if we don't want to distinguish info of patterns that is
                    // a suffix of current node, we can add info to the next
                    // node like this: nxt.nmatches+=N[pnx].nmatches;
                    q.push(N[n].next[i]);
                }
            }
        }
    }

    // for each position, finds the longest pattern that ends here
    vector<int> find(const string &text) {
        int len = (int)text.size();
        vector<int> res(len);
        int n = 0;
        for (int i = 0; i < len; i++) {
            n = N[n].next[text[i] - first];
            res[i] = N[n].end;
        }
        return res;
    }
    // for each position, finds the all that ends here
    vector<vector<int>> find_all(const string &text) {
        int len = (int)text.size();
        vector<vector<int>> res(len);
        int n = 0;
        for (int i = 0; i < len; i++) {
            n = N[n].next[text[i] - first];
            res[i].push_back(N[n].end);
            for (int ind = N[n].output; ind != -1; ind = N[ind].output) {
                assert(N[ind].end != -1);
                res[i].push_back(N[ind].end);
            }
        }
        return res;
    }
};
