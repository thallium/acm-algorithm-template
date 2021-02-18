
const ll MOD = 998244353;

vector<ll>fac(N+1), invFac(N+1);
for(ll i = 1; i <= N; i++) fac[i] = fac[i-1]*i % MOD;
invFac[N] = qpow(fac[N], MOD - 2); // MOD is prime
for(ll i = N; i > 0; i--) invFac[i - 1] = invFac[i] * i % MOD;
auto binom = [&](ll n, ll m) -> int {
  if(m < 0 || n < m) return 0;
  return fac[n] * invFac[m] % MOD * invFac[n - m] % MOD;
};
