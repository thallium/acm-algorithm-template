const ll MOD = 998244353;
ll qpow(ll a, ll b) {
  ll res = 1;
  for(; b; b >>= 1, a = 1ll* a* a % MOD) if(b&1) res = 1ll * res * a % MOD;
  return res;
}

vector<ll>fac(N+1), invFac(N+1);
for(ll i = 1; i <= N; i++) fac[i] = fac[i-1]*i % MOD;
invFac[N] = qpow(fac[N], MOD - 2); // MOD is prime
for(ll i = N; i > 0; i--) invFac[i - 1] = invFac[i] * i % MOD;
auto binom = [&](ll n, ll m) -> int {
  if(m < 0 || n < m) return 0;
  return fac[n] * invFac[m] % MOD * invFac[n - m] % MOD;
};
