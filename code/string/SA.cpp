#include<bits/stdc++.h>
using namespace std;
//O(n log(n)^2),actually calculates cyclic shifts
vector<int> suffix_array(string s) {
    s+="#";
    int n = s.size();
    vector<int> sa(n), rank(n);
    for(int i = 0; i < n; i++)  rank[i] = s[i], sa[i] = i;
    for(int k = 0; k < n; k ? k *= 2 : k = 1) {
        stable_sort(sa.begin(), sa.end(), [&](int i, int j) {
            if(rank[i] == rank[j]) return rank[(i + k) % n] < rank[(j + k) % n];
                return rank[i] < rank[j]; });
        vector<int> nrank(n);
        int r = 0;
        for(int i = 1; i < n; i++) {
            if(rank[sa[i]] != rank[sa[i - 1]]) r++;
            else if(rank[(sa[i] + k) % n] != rank[(sa[i - 1] + k) % n]) r++;
            nrank[sa[i]] = r;
        }
        rank = nrank;
    }
    sa.erase(sa.begin());
    return sa;
}
//O(n log(n)),actually calculates cyclic shifts
vector<int> suffix_array(string s) {
    s+="#";
    int n = s.size(), N = n + 256;
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

//O(n)
vector<int> suffix_array(const string& s, int char_bound) {

    int n=s.size();
    vector<int> a(n);
    if (n == 0) return a;

    if (char_bound != -1) {
        vector<int> aux(char_bound, 0);
        for (int i = 0; i < n; i++) aux[s[i]]++;
        int sum = 0;
        for (int i = 0; i < char_bound; i++) {
            int add = aux[i];
            aux[i] = sum;
            sum += add;
        }
        for (int i = 0; i < n; i++) {
            a[aux[s[i]]++] = i;
        }
    } else {
        iota(a.begin(), a.end(), 0);
        sort(a.begin(), a.end(), [&s](int i, int j) { return s[i] < s[j]; });
    }
    vector<int> sorted_by_second(n);
    vector<int> ptr_group(n);
    vector<int> new_group(n);
    vector<int> group(n);
    group[a[0]] = 0;
    for (int i = 1; i < n; i++) {
        group[a[i]] = group[a[i - 1]] + (!(s[a[i]] == s[a[i - 1]]));
    }
    int cnt = group[a[n - 1]] + 1;
    int step = 1;
    while (cnt < n) {
        int at = 0;
        for (int i = n - step; i < n; i++) {
            sorted_by_second[at++] = i;
        }
        for (int i = 0; i < n; i++) {
            if (a[i] - step >= 0) {
                sorted_by_second[at++] = a[i] - step;
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            ptr_group[group[a[i]]] = i;
        }
        for (int i = 0; i < n; i++) {
            int x = sorted_by_second[i];
            a[ptr_group[group[x]]++] = x;
        }
        new_group[a[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (group[a[i]] != group[a[i - 1]]) {
                new_group[a[i]] = new_group[a[i - 1]] + 1;
            } else {
                int pre = (a[i - 1] + step >= n ? -1 : group[a[i - 1] + step]);
                int cur = (a[i] + step >= n ? -1 : group[a[i] + step]);
                new_group[a[i]] = new_group[a[i - 1]] + (pre != cur);
            }
        }
        swap(group, new_group);
        cnt = group[a[n - 1]] + 1;
        step <<= 1;
    }
    return a;
}


vector<int> build_lcp(const string& s, const vector<int>& sa) {
    int n=s.size();
    vector<int> pos(n);
    for (int i = 0; i < n; i++) pos[sa[i]] = i;

    vector<int> lcp(max(n - 1, 0));
    int k = 0;
    for (int i = 0; i < n; i++) {
        k = max(k - 1, 0);
        if (pos[i] == n - 1) k = 0;
        else {
            int j = sa[pos[i] + 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
            lcp[pos[i]] = k;
        }
    }
    return lcp;
}
