vector<ll>fac(N+1);

const ll N = 10;
double qpow(double a, int b) {
    double res = 1;
    for(;b; b>>=1, a = a*a) if(b&1) res=res*a;
    return res;
}
vector<ll>fac(N+1);
fac[0] = 1;
for(ll i = 1; i <= N; i++) fac[i] = fac[i-1]*i;
auto binom = [&](ll n, ll m) -> int {
  if(m < 0 || n < m) return 0;
  return fac[n] / (fac[m]*fac[n-m]);
};
