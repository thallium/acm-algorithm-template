// a*x=1(mod p) x=a^(p-2)
inline int qpow(long long a, int b) {
  int ans = 1;
  a = (a % p + p) % p;
  while(b) {
    if (b & 1) ans = (a * ans) % p;
    a = (a * a) % p;
    b>>=1;
  }
  return ans;
}
//linear time
inv[1] = 1;
for (int i = 2; i <= n; ++i) inv[i] = (long long)(p - p / i) * inv[p % i] % p;
// calculate n pick m mod p
//when n and m are not too big, ans=fact[n]*inv[m]*inv[n-m]%p
fact[0] = 1;
for (int i = 1; i < maxn; i++) {
    fact[i] = fact[i - 1] * i %mod;
}
inv[maxn - 1] = power(fact[maxn - 1], mod - 2);
for (int i = maxn - 2; i >= 0; i--) {
    inv[i] = inv[i + 1] * (i + 1) %mod;
}
// when n and m are big but p is small
long long Lucas(long long n, long long m, long long p) {
  if (m == 0) return 1;
  return (C(n % p, m % p, p) * Lucas(n / p, m / p, p)) % p;
}