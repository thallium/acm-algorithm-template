#include <vector>
#include <array>
#include <string>
#include <queue>
/** Modified from:
 * https://github.com/kth-competitive-programming/kactl/blob/master/content/strings/AhoCorasick.h
 * If there's no duplicated patterns, just call the constructor, otherwise handle it beforehand
 * by yourself, or use the return value of insert
 * empty patterns are not allowed.
 * Time: construction takes $O(26N)$,
 * where $N =$ sum of length of patterns. find(x) is $O(N)$, where N = length of
 * x. findAll is $O(N+M)$ where M is number of occurrence of all pattern (up to N*sqrt(N)) */

template<int alpha = 26, int first = 'a'>
struct AhoCorasick {
    struct Node {
        // back: failure link, points to longest suffix that is in the trie.
        // end: longest pattern that ends here, is -1 if no patten ends here.
        // nmatches: number of patterns that is a suffix of current node
        // output: output link, points to the longest pattern that is a suffix
        // of current node
        int back = 0, end = -1, nmatches = 0, output = -1;
        std::array<int, alpha> next;
        Node() { std::fill(next.begin(), next.end(), -1); }
    };

    std::vector<Node> N;

    AhoCorasick() : N(1) {}
    AhoCorasick(const std::vector<std::string>& patterns) {
        for (int i = 0; i < (int)patterns.size(); i++) {
            insert(patterns[i], i);
        }
        build();
    }

    // returns -1 if there's no duplicated pattern already in the trie
    // returns the id of the duplicated pattern otherwise
    int insert(const std::string &s, int j) { // j: id of string s
        assert(!s.empty());
        int n = 0;
        for (char c : s) {
            if (N[n].next[c - first] == -1) {
                N[n].next[c - first] = (int)N.size();
                N.emplace_back();
            }
            n = N[n].next[c - first];
        }
        if (N[n].end != -1) {
            return N[n].end;
        }
        N[n].end = j;
        N[n].nmatches++;
        return -1;
    }

    void build() {
        std::queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < alpha; i++) {
                int fail = u ? N[N[u].back].next[i] : 0;
                auto v = N[u].next[i];
                if (v == -1) N[u].next[i] = fail;
                else {
                    N[v].back = fail;
                    // if prev is an end node, then set output to prev node,
                    // otherwise set to output link of prev node
                    N[v].output = N[fail].end == -1 ? N[fail].output : fail;
                    N[v].nmatches += N[fail].nmatches;
                    q.push(v);
                }
            }
        }
    }

    // for each position, finds the longest pattern that ends here
    std::vector<int> find(const std::string &text) {
        int len = (int)text.size();
        std::vector<int> res(len);
        int n = 0;
        for (int i = 0; i < len; i++) {
            n = N[n].next[text[i] - first];
            res[i] = N[n].end;
        }
        return res;
    }

    // for each position, finds all patterns that ends here
    std::vector<std::vector<int>> find_all(const std::string &text) {
        int len = (int)text.size();
        std::vector<std::vector<int>> res(len);
        int n = 0;
        for (int i = 0; i < len; i++) {
            n = N[n].next[text[i] - first];
            if (N[n].end != -1) {
                res[i].push_back(N[n].end);
            }
            for (int ind = N[n].output; ind != -1; ind = N[ind].output) {
                assert(N[ind].end != -1);
                res[i].push_back(N[ind].end);
            }
        }
        return res;
    }

    // finds the number of occurrence of each pattern
    std::vector<int> find_cnt(const std::string& text, int num_of_patterns) {
        std::vector<int> cnt(num_of_patterns);
        int p = 0;
        for (auto c : text) {
            p = N[p].next[c - first];
            if (N[p].end != -1) {
                cnt[N[p].end] += 1;
            }
            for (int i = N[p].output; i != -1; i = N[i].output) {
                cnt[N[i].end]++;
            }
        }
        return cnt;
    }
};
