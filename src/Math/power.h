ll qpow(ll a, ll b) {
  ll res = 1;
  for(; b; b >>= 1, a = 1ll* a* a % MOD) if(b&1) res = 1ll * res * a % MOD;
  return res;
}
