const ll MOD = 998244353;
vector<ll> inv(n+1);
inv[1]=1;
for(int i = 2; i < n + 1; ++i) inv[i] = MOD - (MOD/i) * inv[MOD % i] % MOD;
