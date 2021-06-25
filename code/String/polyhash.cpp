#include<bits/stdc++.h>
using namespace std;
using ll = long long;
struct PolyHash {
    static constexpr int mod = (int)1e9 + 123;
    static vector<int> pow;
    static constexpr int base = 233;

    vector<int> pref;
    PolyHash(const string &s) : pref(s.size() + 1) {
        assert(base < mod);
        int n = (int)s.size();
        while ((int)pow.size() <= n) {
            pow.push_back((ll)pow.back() * base % mod);
        }
        for (int i = 0; i < n; i++) {
            pref[i + 1] = ((ll)pref[i] * base + s[i]) % mod;
        }
    }

    int get_hash() {
        return pref.back();
    }

    int substr(int pos, int len) {
        return (pref[pos + len] - (ll)pref[pos] * pow[len] % mod + mod) % mod;
    }
};
vector<int> PolyHash::pow{1};
