typedef double T;

const double EPS = 1e-9;
inline int sign(double a) { return a < -EPS ? -1 : a > EPS; }
inline int cmp(double a, double b){ return sign(a-b); }

struct P {
  T x,y;
  P() {}
	P(T _x, T _y) : x(_x), y(_y) {}
  P operator+(P p) {return {x+p.x, y+p.y};}
  P operator-(P p) {return {x-p.x, y-p.y};}
  P operator*(T d) {return {x*d, y*d};}
  P operator/(T d) {return {x/d, y/d};} // only for floatingpoint

  bool operator<(P p) const { 
    int c = cmp(x, p.x);
    if (c) return c == -1;
    return cmp(y, p.y) == -1;
  }	
  bool operator==(P o) const{
		return cmp(x,o.x) == 0 && cmp(y,o.y) == 0;
	}
  double dot(P p) { return x * p.x + y * p.y; }
  double det(P p) { return x * p.y - y * p.x; }

	double distTo(P p) { return (*this-p).abs(); }
	double alpha() { return atan2(y, x); }
  void read() { cin>>x>>y; }
  void write() {cout<<"("<<x<<","<<y<<")"<<endl;}
  double abs() { return sqrt(abs2());}
	double abs2() { return x * x + y * y; }
	P rot90() { return P(-y,x);}
	P unit() { return *this/abs(); }
  int quad() const { return sign(y) == 1 || (sign(y) == 0 && sign(x) >= 0); }
	P rot(double an){ return {x*cos(an)-y*sin(an),x*sin(an) + y*cos(an)}; }
};

#define cross(p1,p2,p3) ((p2.x-p1.x)*(p3.y-p1.y)-(p3.x-p1.x)*(p2.y-p1.y))
#define crossOp(p1,p2,p3) sign(cross(p1,p2,p3))

bool isConvex(vector<P> p) {
  bool hasPos=false, hasNeg=false;
  for (int i=0, n=p.size(); i<n; i++) {
    int o = cross(p[i], p[(i+1)%n], p[(i+2)%n]);
    if (o > 0) hasPos = true;
    if (o < 0) hasNeg = true;
  }
  return !(hasPos && hasNeg);
}

bool half(P p) {
  assert(p.x != 0 || p.y != 0); // (0, 0) is not covered
  return p.y > 0 || (p.y == 0 && p.x < 0);
}

void polarSortAround(P o, vector<P> &v) {
  sort(v.begin(), v.end(), [&o](P v, P w) {
      return make_tuple(half(v-o), 0) <
        make_tuple(half(w-o), cross(o, v, w));
  });
}

P proj(P p1, P p2, P q) {
	P dir = p2 - p1;
	return p1 + dir * (dir.dot(q - p1) / dir.abs2());
}
  
P reflect(P p1, P p2, P q){
	return proj(p1,p2,q) * 2 - q;
}

// tested with https://open.kattis.com/problems/closestpair2
pair<P, P> closest(vector<P> v) {
  assert(sz(v) > 1);
  set <P> S;
  sort(v.begin(), v.end(), [](P a, P b) { return a.y < b.y; });
  pair<T, pair<P, P>> ret{(T)1e18, {P(), P()}};
  int j = 0;
  for(P p : v) {
    P d { 1 + (T) sqrt(ret.first), 0 };
    while(p.y - v[j].y >= d.x) S.erase(v[j++]);
    auto lo = S.lower_bound(p - d), hi = S.upper_bound(p + d);
    for(; lo != hi; ++lo) {
      ret = min(ret, {(p - (*lo)).abs2(), {*lo, p}});
    }
    S.insert(p);
  }
  return ret.second;
}
