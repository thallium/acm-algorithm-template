typedef double T;

struct P {
  T x,y;
  P() {}
	P(T _x, T _y) : x(_x), y(_y) {}
  P operator+(P p) {return {x+p.x, y+p.y};}
  P operator-(P p) {return {x-p.x, y-p.y};}
  P operator*(T d) {return {x*d, y*d};}
  P operator/(T d) {return {x/d, y/d};} // only for floatingpoint
  void read() { cin>>x>>y; }
  void write() {cout<<"("<<x<<","<<y<<")"<<endl;}
};

bool operator==(P a, P b) {return a.x == b.x && a.y == b.y;}
bool operator!=(P a, P b) {return !(a == b);}

T sq(P p) {return p.x*p.x + p.y*p.y;}

double abs(P p) {return sqrt(sq(p));}

template <typename T> int sgn(T x) {
  return (T(0) < x) - (x < T(0));
}

P translate(P v, P p) {return p+v;}

P rot(P p, double a) {
  return {p.x*cos(a) - p.y*sin(a), p.x*sin(a) + p.y*cos(a)};
}

P perp(P p) {return {-p.y, p.x};}

T cross(P v, P w) {return v.x*w.y - v.y*w.x;}
T dot(P v, P w) {return v.x*w.x + v.y*w.y;}

P linearTransfo(P p, P q, P r, P fp, P fq) {
  P pq = q-p, num{cross(pq, fq-fp), dot(pq, fq-fp)};
  return fp + P{cross(r-p, num), dot(r-p, num)} / sq(pq);
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

double orientedAngle(P a, P b, P c) {
  if (orient(a,b,c) >= 0)
    return angle(b-a, c-a);
  else
    return 2*M_PI - angle(b-a, c-a);
}

bool isConvex(vector<P> p) {
  bool hasPos=false, hasNeg=false;
  for (int i=0, n=p.size(); i<n; i++) {
    int o = orient(p[i], p[(i+1)%n], p[(i+2)%n]);
    if (o > 0) hasPos = true;
    if (o < 0) hasNeg = true;
  }
  return !(hasPos && hasNeg);
}

bool half(P p) {
  assert(p.x != 0 || p.y != 0);
  return p.y > 0 || (p.y == 0 && p.x < 0);
}

void polarSort(vector<P> &v) {
  sort(v.begin(), v.end(), [](P v, P w) {
      return make_tuple(half(v), 0, sq(v)) <
      make_tuple(half(w), cross(v,w), sq(v));
      });
}

void polarSortAround(P o, vector<P> &v) {
  sort(v.begin(), v.end(), [](P v, P w) {
      return make_tuple(half(v-o), 0)) <
        make_tuple(half(w-o), cross(v-o, w-o));
  });
}
