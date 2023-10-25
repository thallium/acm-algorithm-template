#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using i128 = __int128;
int main() {
    const int N = 1e6;
    vector<ll> pow(N + 1);
    ll base = 233, mod = 1'000'000'000'000'000'003;
    pow[0] = 1;
    for (int i = 1; i <= N; i++) {
        pow[i] = (i128)pow[i - 1] * base % mod;
    }

    auto hash = [&](const string& s) {
        int sz = (int)size(s);
        vector<ll> pref(sz + 1);
        for (int i = 0; i < sz; i++) {
            pref[i + 1] = ((i128)pref[i] * base % mod + s[i]) % mod;
        }
        return pref;
    };

    // [l, r)
    auto substr = [&](const vector<ll>& h, int l, int r) {
        return (h[r] - (i128)h[l] * pow[r - l] % mod + mod) % mod;
    };

    auto concat = [&](ll lhs, ll rhs, int len_rhs) {
        return ((i128)lhs * pow[len_rhs] % mod + rhs) % mod;
    };

}
