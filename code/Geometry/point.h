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
  
P linearTransfo(P p, P q, P r, P fp, P fq) {
  return fp + (r-p) * (fq-fp) / (q-p);
}

bool isPerp(P v, P w) {return dot(v,w) == 0;}

double angle(P v, P w) {
  return acos(clamp(dot(v,w) / abs(v) / abs(w), -1.0, 1.0));
}

T orient(P a, P b, P c) {return cross(b-a,c-a);}

bool inAngle(P a, P b, P c, P p) {
  assert(orient(a,b,c) != 0);
  if (orient(a,b,c) < 0) swap(b,c);
  return orient(a,b,p) >= 0 && orient(a,c,p) <= 0;
}

double orientedAngle(P a, P b, P c) {
  if (orient(a,b,c) >= 0)
    return angle(b-a, c-a);
  else
    return 2*M_PI - angle(b-a, c-a);
}

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
  sort(v.begin(), v.end(), [](P v, P w) {
      return make_tuple(half(v-o), 0)) <
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
