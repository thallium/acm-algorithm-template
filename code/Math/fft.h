// for polynomial multiplication, tested with https://open.kattis.com/problems/polymul2
typedef double T;
typedef complex<T> C;

void fft(vector <C> &a, bool invert){
  int n = sz(a);
  for(int i=0,j=0;i<n;++i) {
    if(i>j) swap(a[i],a[j]);
    for(int k=n>>1;(j^=k)<k;k>>=1);
  }
  for (int len=2;len<=n;len<<=1){
    double ang = 2*M_PI/len*(invert?-1:1);
    C wlen(cos(ang), sin(ang));
    for (int i=0;i<n;i+=len){
      C w(1);
      for (int j=0;j<len/2;j++){
        // if((j & 511) == 511)w = C(cos(ang * j), sin(ang * j));	
        C u = a[i+j], v = a[i+j+len/2]*w;
        a[i+j] = u+v;
        a[i+j+len/2] = u-v;
        w *= wlen;
      }
    }
  }
  if (invert){
    for (int i=0;i<n;i++) a[i] /= n;
  }
}

void conv(const vector<ll> &a,const vector<ll> &b,vector<ll> &res){
  vector <C> fa(all(a)), fb(all(b));
  int n = 1;
  while (n < max(sz(a),sz(b))) n <<= 1; n <<= 1;
  fa.resize(n); fb.resize(n);
  fft(fa,false); fft(fb,false);
  for (int i=0;i<n;i++) fa[i] *= fb[i];
  fft(fa,true);
  res.resize(n);
  for (int i=0;i<n;i++) res[i] = ((ll)(fa[i].real()+(fa[i].real()>0?0.5:-0.5)));
}
