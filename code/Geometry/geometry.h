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
struct L {
  P ps[2]; P v; T c;
  L() {}
  P& operator[](int i) { return ps[i]; }
  // From direction vector v and offset c
  L(P v, T c) : v(v), c(c) {}
  // From equation ax+by=c
  L(T a, T b, T c) : v({b,-a}), c(c) {}
  // From points P and Q
  L(P p, P q) : v(q-p), c(cross(P(0, 0), v,p)) {
    ps[0] = p;
    ps[1] = q;
  }
  P dir() { return ps[1] - ps[0]; }
  bool include(P p) { return sign((ps[1] - ps[0]).det(p - ps[0])) > 0; }
  T side(P p) {return cross(P(0, 0), v,p)-c;}
  T dist(P p) {return abs(side(p)) / v.abs();}
  T sqDist(P p) {return side(p)*side(p) / (double)v.abs();}
  L perpThrough(P p) {return L(p, p + v.rot90());}
  bool cmpProj(P p, P q) {
    return v.dot(p) < v.dot(q);
  }
  L translate(P t) {return L(v, c + cross(P(0,0), v,t));}
  L shiftLeft(double dist) {return L(v, c + dist*v.abs());}
  L shiftRight(double dist) {return L(v, c - dist*v.abs());}
};
bool chkLL(P p1, P p2, P q1, P q2) {
	double a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
	return sign(a1+a2) != 0;
}
P isLL(P p1, P p2, P q1, P q2) {
	double a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
	return (p1 * a2 + p2 * a1) / (a1 + a2);
}
P isLL(L l1,L l2){ return isLL(l1[0],l1[1],l2[0],l2[1]); }
bool parallel(L l0, L l1) { return sign( l0.dir().det( l1.dir() ) ) == 0; }
bool sameDir(L l0, L l1) { return parallel(l0, l1) && sign(l0.dir().dot(l1.dir()) ) == 1; }
bool cmp (P a,  P b) {
	if (a.quad() != b.quad()) {
		return a.quad() < b.quad();
	} else {
		return sign( a.det(b) ) > 0;
	}
}
bool operator < (L l0, L l1) {
	if (sameDir(l0, l1)) {
		return l1.include(l0[0]);
	} else {
		return cmp( l0.dir(), l1.dir() );
	}
}
bool check(L u, L v, L w) { 
	return w.include(isLL(u,v)); 
}
vector<P> halfPlaneIS(vector<L> &l) {
	sort(l.begin(), l.end());
	deque<L> q;
	for (int i = 0; i < (int)l.size(); ++i) {
		if (i && sameDir(l[i], l[i - 1])) continue;
		while (q.size() > 1 && !check(q[q.size() - 2], q[q.size() - 1], l[i])) q.pop_back();
		while (q.size() > 1 && !check(q[1], q[0], l[i])) q.pop_front();
		q.push_back(l[i]);
	}
	while (q.size() > 2 && !check(q[q.size() - 2], q[q.size() - 1], q[0])) q.pop_back();
	while (q.size() > 2 && !check(q[1], q[0], q[q.size() - 1])) q.pop_front();
	vector<P> ret;
	for (int i = 0; i < (int)q.size(); ++i) ret.push_back(isLL(q[i], q[(i + 1) % q.size()]));
	return ret;
}
struct cmpX {
  bool operator()(P a, P b) const {
    return make_pair(a.x, a.y) < make_pair(b.x, b.y);
  }
};
bool intersect(double l1,double r1,double l2,double r2){
	if(l1>r1) swap(l1,r1); if(l2>r2) swap(l2,r2); 
	return !( cmp(r1,l2) == -1 || cmp(r2,l1) == -1 );
}
bool isSS(P p1, P p2, P q1, P q2){
	return intersect(p1.x,p2.x,q1.x,q2.x) && intersect(p1.y,p2.y,q1.y,q2.y) && 
	crossOp(p1,p2,q1) * crossOp(p1,p2,q2) <= 0 && crossOp(q1,q2,p1)
			* crossOp(q1,q2,p2) <= 0;
}
bool isSS_strict(P p1, P p2, P q1, P q2){
	return crossOp(p1,p2,q1) * crossOp(p1,p2,q2) < 0 && crossOp(q1,q2,p1)
			* crossOp(q1,q2,p2) < 0;
}
bool isMiddle(double a, double m, double b) {
	return sign(a - m) == 0 || sign(b - m) == 0 || (a < m != b < m);
}
bool isMiddle(P a, P m, P b) {
	return isMiddle(a.x, m.x, b.x) && isMiddle(a.y, m.y, b.y);
}
bool onSeg(P p1, P p2, P q){
	return crossOp(p1,p2,q) == 0 && isMiddle(p1, q, p2);
}
bool onSeg_strict(P p1, P p2, P q){
	return crossOp(p1,p2,q) == 0 && sign((q-p1).dot(p1-p2)) * sign((q-p2).dot(p1-p2)) < 0;
}
double nearest(P p1,P p2,P q){
	P h = proj(p1,p2,q);
	if(isMiddle(p1,h,p2))
		return q.distTo(h);
	return min(p1.distTo(q),p2.distTo(q));
}
double disSS(P p1, P p2, P q1, P q2){
	if(isSS(p1,p2,q1,q2)) return 0;
	return min(min(nearest(p1,p2,q1),nearest(p1,p2,q2)), min(nearest(q1,q2,p1),nearest(q1,q2,p2)));
}
double DEG_to_RAD(double d) { return d*M_PI/180.0; }
double RAD_to_DEG(double r) { return r*180.0/M_PI; }
double rad(P p1,P p2){
	return atan2l(p1.det(p2),p1.dot(p2));
}
bool inAngle(P a, P b, P c, P p) {
  assert(crossOp(a,b,c) != 0);
  if (crossOp(a,b,c) < 0) swap(b,c);
  return crossOp(a,b,p) >= 0 && crossOp(a,c,p) <= 0;
}
double angle(P v, P w) {
  return acos(clamp(v.dot(w) / v.abs() / w.abs(), -1.0, 1.0));
}
double orientedAngle(P a, P b, P c) { // BAC
  if (crossOp(a,b,c) >= 0) return angle(b-a, c-a);
  else return 2*M_PI - angle(b-a, c-a);
}
// double chord(double r, double ang) return sqrt(2*r*r*(1-cos(ang))); // or 2*r*sin(ang/2)
// double secarea(double r, double ang) {return (ang/2)*(r*r);} // rad
// double segarea(double r, double ang) {return secarea(r, ang) - r*r*sin(ang)/2;}
int type(P o1,double r1,P o2,double r2){
	double d = o1.distTo(o2);
	if(cmp(d,r1+r2) == 1) return 4; // outside each other
	if(cmp(d,r1+r2) == 0) return 3; // touch outside
	if(cmp(d,abs(r1-r2)) == 1) return 2; // one inside another
	if(cmp(d,abs(r1-r2)) == 0) return 1; // touch inside
	return 0;
}
vector<P> isCL(P o,double r,P p1,P p2){
	if (cmp(abs((o-p1).det(p2-p1)/p1.distTo(p2)),r)>0) return {};
	double x = (p1-o).dot(p2-p1), y = (p2-p1).abs2(), d = x * x - y * ((p1-o).abs2() - r*r);
	d = max(d,0.0); P m = p1 - (p2-p1)*(x/y), dr = (p2-p1)*(sqrt(d)/y);
	return {m-dr,m+dr}; //along dir: p1->p2
}
vector<P> isCC(P o1, double r1, P o2, double r2) { //need to check whether two circles are the same
	double d = o1.distTo(o2); 
	if (cmp(d, r1 + r2) == 1) return {};
	if (cmp(d,abs(r1-r2))==-1) return {};
	d = min(d, r1 + r2);
	double y = (r1 * r1 + d * d - r2 * r2) / (2 * d), x = sqrt(r1 * r1 - y * y);
	P dr = (o2 - o1).unit();
	P q1 = o1 + dr * y, q2 = dr.rot90() * x;
	return {q1-q2,q1+q2};//along circle 1
}
vector<P> tanCP(P o, double r, P p) {
	double x = (p - o).abs2(), d = x - r * r;
	if (sign(d) <= 0) return {}; // on circle => no tangent
	P q1 = o + (p - o) * (r * r / x);
	P q2 = (p - o).rot90() * (r * sqrt(d) / x);
	return {q1-q2,q1+q2}; //counter clock-wise
}
vector<L> extanCC(P o1, double r1, P o2, double r2) {
	vector<L> ret;
	if (cmp(r1, r2) == 0) {
		P dr = (o2 - o1).unit().rot90() * r1;
		ret.push_back(L(o1 + dr, o2 + dr)), ret.push_back(L(o1 - dr, o2 - dr));
	} else {
		P p = (o2 * r1 - o1 * r2) / (r1 - r2);
		vector<P> ps = tanCP(o1, r1, p), qs = tanCP(o2, r2, p);
		for(int i = 0; i < min(ps.size(),qs.size());i++) ret.push_back(L(ps[i], qs[i])); //c1 counter-clock wise
	}
	return ret;
}
vector<L> intanCC(P o1, double r1, P o2, double r2) {
	vector<L> ret;
	P p = (o1 * r2 + o2 * r1) / (r1 + r2);
	vector<P> ps = tanCP(o1,r1,p), qs = tanCP(o2,r2,p);
	for(int i = 0; i < min(ps.size(),qs.size()); i++) ret.push_back(L(ps[i], qs[i])); //c1 counter-clock wise
	return ret;
}
double areaCT(double r, P p1, P p2){
	vector<P> is = isCL(P(0,0),r,p1,p2);
	if(is.empty()) return r*r*rad(p1,p2)/2;
	bool b1 = cmp(p1.abs2(),r*r) == 1, b2 = cmp(p2.abs2(), r*r) == 1;
	if(b1 && b2){
		if(sign((p1-is[0]).dot(p2-is[0])) <= 0 &&
			sign((p1-is[0]).dot(p2-is[0])) <= 0)
		return r*r*(rad(p1,is[0]) + rad(is[1],p2))/2 + is[0].det(is[1])/2;
		else return r*r*rad(p1,p2)/2;
	}
	if(b1) return (r*r*rad(p1,is[0]) + is[0].det(p2))/2;
	if(b2) return (p1.det(is[1]) + r*r*rad(is[1],p2))/2;
	return p1.det(p2)/2;
}
P inCenter(P A, P B, P C) {
	double a = (B - C).abs(), b = (C - A).abs(), c = (A - B).abs();
	return (A * a + B * b + C * c) / (a + b + c);
}
P circumCenter(P a, P b, P c) { 
	P bb = b - a, cc = c - a;
	double db = bb.abs2(), dc = cc.abs2(), d = 2 * bb.det(cc);
	return a - P(bb.y * dc - cc.y * db, cc.x * db - bb.x * dc) / d;
}
P othroCenter(P a, P b, P c) { 
	P ba = b - a, ca = c - a, bc = b - c;
	double Y = ba.y * ca.y * bc.y,
	A = ca.x * ba.y - ba.x * ca.y,
	x0 = (Y + ca.x * ba.y * b.x - ba.x * ca.y * c.x) / A,
	y0 = -ba.x * (x0 - c.x) / ba.y + ca.y;
	return {x0, y0};
}
//polygon
double area(vector<P> ps){
	double ret = 0; 
  for(int i=0; i< ps.size(); i++) ret += ps[i].det(ps[(i+1)%ps.size()]); 
	return ret/2;
}
int contain(vector<P> ps, P p){ //2:inside,1:on_seg,0:outside
	int n = ps.size(), ret = 0; 
	for(int i = 0; i < n; i++) {
		P u=ps[i],v=ps[(i+1)%n];
		if(onSeg(u,v,p)) return 1;
		if(cmp(u.y,v.y)<=0) swap(u,v);
		if(cmp(p.y,u.y) >0 || cmp(p.y,v.y) <= 0) continue;
		ret ^= crossOp(p,u,v) > 0;
	}
	return ret*2;
}
vector<P> convexHull(vector<P> ps) {
	int n = ps.size(); if(n <= 1) return ps;
	sort(ps.begin(), ps.end());
	vector<P> qs(n * 2); int k = 0;
	for (int i = 0; i < n; qs[k++] = ps[i++]) 
		while (k > 1 && crossOp(qs[k - 2], qs[k - 1], ps[i]) <= 0) --k;
	for (int i = n - 2, t = k; i >= 0; qs[k++] = ps[i--])
		while (k > t && crossOp(qs[k - 2], qs[k - 1], ps[i]) <= 0) --k;
	qs.resize(k - 1);
	return qs;
}
vector<P> convexHullNonStrict(vector<P> ps) {
	//caution: need to unique the Ps first
	int n = ps.size(); if(n <= 1) return ps;
	sort(ps.begin(), ps.end());
	vector<P> qs(n * 2); int k = 0;
	for (int i = 0; i < n; qs[k++] = ps[i++]) 
		while (k > 1 && crossOp(qs[k - 2], qs[k - 1], ps[i]) < 0) --k;
	for (int i = n - 2, t = k; i >= 0; qs[k++] = ps[i--])
		while (k > t && crossOp(qs[k - 2], qs[k - 1], ps[i]) < 0) --k;
	qs.resize(k - 1);
	return qs;
}
double convexDiameter(vector<P> ps){
	int n = ps.size(); if(n <= 1) return 0;
	int is = 0, js = 0; for(int k = 1; k < n; k++) is = ps[k]<ps[is]?k:is, js = ps[js] < ps[k]?k:js;
	int i = is, j = js;
	double ret = ps[i].distTo(ps[j]);
	do{
		if((ps[(i+1)%n]-ps[i]).det(ps[(j+1)%n]-ps[j]) >= 0)
			(++j)%=n;
		else
			(++i)%=n;
		ret = max(ret,ps[i].distTo(ps[j]));
	}while(i!=is || j!=js);
	return ret;
}
vector<P> convexCut(const vector<P>&ps, P q1, P q2) {
	vector<P> qs;
	int n = ps.size();
	for(int i = 0; i<n; i++) {
		P p1 = ps[i], p2 = ps[(i+1)%n];
		int d1 = crossOp(q1,q2,p1), d2 = crossOp(q1,q2,p2);
		if(d1 >= 0) qs.push_back(p1);
		if(d1 * d2 < 0) qs.push_back(isLL(p1,p2,q1,q2));
	}
	return qs;
}
