struct L {
  P v; T c;
  // From direction vector v and offset c
  L(P v, T c) : v(v), c(c) {}
  // From equation ax+by=c
  L(T a, T b, T c) : v({b,-a}), c(c) {}
  // From points P and Q
  L(P p, P q) : v(q-p), c(cross(v,p)) {}
  // Will be defined later:
  // - these work with T = int
  T side(P p) {return cross(v,p)-c;}
  double dist(P p) {return abs(side(p)) / abs(v);}
  double sqDist(P p) {return side(p)*side(p) / (double)sq(v);}
  L perpThrough(P p) {return {p, p + perp(v)};}
  bool cmpProj(P p, P q) {
    return dot(v,p) < dot(v,q);
  }
  L translate(P t) {return {v, c + cross(v,t)};}
  L shiftLeft(double dist) {return {v, c + dist*abs(v)};}
  L shiftRight(double dist) {return {v, c - dist*abs(v)};}
  P proj(P p) {return p - perp(v)*side(p)/sq(v);}
  P refl(P p) {return p - perp(v)*2*side(p)/sq(v);}
};

bool inter(L l1, L l2, P &out) {
  T d = cross(l1.v, l2.v);
  if (d == 0) return false;
  out = (l2.v*l1.c - l1.v*l2.c) / d; // requires floating-point
  return true;
}

L bisector(L l1, L l2, bool interior) {
  assert(cross(l1.v, l2.v) != 0); // l1 and l2 cannot be parallel!
  double sign = interior ? 1 : -1;
  return {l2.v/abs(l2.v) + l1.v/abs(l1.v) * sign,
    l2.c/abs(l2.v) + l1.c/abs(l1.v) * sign};
}
