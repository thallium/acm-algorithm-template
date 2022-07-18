#include<bits/stdc++.h>
using ll=long long;
//   {g, x, y}: ax+by=gcd(a,b)
tuple<ll, ll, ll> exgcd(ll a, ll b) {
    if (b==0) return {a, 1, 0};
    auto [g, x, y]=exgcd(b, a%b);
    return {g, y, x-a/b*y};
}
/*
solve ax+by=c, equivalently ax=c (mod b)
all solutions: x=x0+b/g*t, y=y0-a/g*t
smallest positive x=(x0%t+t)%t, where t=b/g
*/
bool liEu(ll a, ll b, ll c, ll& x, ll& y) {
    ll g;
    tie(g, x, y)=exgcd(a, b);
    if (c % g != 0) return false;
    ll k = c / g;
    x *= k;
    y *= k;
    // smallest positive x:
    // b/=g;
    // x=(x%b+b)%b;
    return true;
}
