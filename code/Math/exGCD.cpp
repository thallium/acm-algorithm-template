// ax+by=gcd(a,b)
ll ex_gcd(ll a, ll b, ll& x, ll& y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  ll d = ex_gcd(b, a % b, x, y);
  ll temp = x;
  x = y;
  y = temp - a / b * y;
  return d;
}
//the smallest integer solution to ax+by=c;
bool liEu(ll a, ll b, ll c, ll& x, ll& y) {
  ll d = ex_gcd(a, b, x, y);
  if (c % d != 0) return 0;
  ll k = c / d;
  x *= k;
  y *= k;
  return 1;
}