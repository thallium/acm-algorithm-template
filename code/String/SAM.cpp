#include <bits/stdc++.h>
using namespace std;
struct SAM {
    vector<map<char,int>> edges; // edges[i]  : the labeled edges from node i
    vector<int> link, length;            // link[i]   : the parent of i
    int last;                    // the index of the equivalence class of the whole string

    SAM(string s) {
        // add the initial node
        edges.emplace_back();
        link.push_back(-1);
        length.push_back(0);
        last = 0;

        for(auto ch:s){
            // construct r
            edges.push_back(map<char,int>());
            length.push_back(length[last]+1);
            link.push_back(0);
            int r = edges.size() - 1;

            // add edges to r and find p with link to q
            int p = last;
            while(p >= 0 && edges[p].find(ch) == edges[p].end()) {
                edges[p][ch] = r;
                p = link[p];
            }
            if(p != -1) {
                int q = edges[p][ch];
                if(length[p] + 1 == length[q]) {
                    // we do not have to split q, just set the correct suffix link
                    link[r] = q;
                } else {
                    // we have to split, add q'
                    edges.push_back(edges[q]); // copy edges of q
                    length.push_back(length[p] + 1);
                    link.push_back(link[q]); // copy parent of q
                    int qq = edges.size()-1;
                    // add qq as the new parent of q and r
                    link[q] = qq;
                    link[r] = qq;
                    // move short classes pointing to q to point to q'
                    while(p >= 0 && edges[p][ch] == q) {
                        edges[p][ch] = qq;
                        p = link[p];
                    }
                }
            }
            last = r;
        }
    }
};
