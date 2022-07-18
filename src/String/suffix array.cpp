#include<bits/stdc++.h>
//O(n log(n)),actually calculates cyclic shifts
vector<int> suffix_array(string s) {
    s+="#";
    int n = (int)s.size(), N = n + 256;
    vector<int> sa(n), ra(n);
    for(int i = 0; i < n; i++) sa[i] = i, ra[i] = s[i];
    for(int k = 0; k < n; k ? k *= 2 : k++) {
        vector<int> nsa(sa), nra(n), cnt(N);
        for(int i = 0; i < n; i++) nsa[i] = (nsa[i] - k + n) % n;
        for(int i = 0; i < n; i++) cnt[ra[i]]++;
        for(int i = 1; i < N; i++) cnt[i] += cnt[i - 1];
        for(int i = n - 1; i >= 0; i--) sa[--cnt[ra[nsa[i]]]] = nsa[i];
 
        int r = 0;
        for(int i = 1; i < n; i++) {
            if(ra[sa[i]] != ra[sa[i - 1]]) r++;
            else if(ra[(sa[i] + k) % n] != ra[(sa[i - 1] + k) % n]) r++;
            nra[sa[i]] = r;
        }
        ra = nra;
    }
    sa.erase(sa.begin());
    return sa;
}
vector<int> build_lcp(const string& s, const vector<int>& sa) { // lcp of sa[i] and sa[i-1]
    int n = (int)s.size();
    vector<int> pos(n);
    for (int i = 0; i < n; i++) pos[sa[i]] = i;
    vector<int> lcp(n);
    for (int i = 0, k = 0; i < n; i++) {
        if (pos[i] == 0) continue;
        if (k) k--;
        while (s[i+k] == s[sa[pos[i]-1]+k]) k++;
        lcp[pos[i]] = k;
    }
    return lcp;
}
