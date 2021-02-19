bool inDisk(P a, P b, P p) {
  return dot(a-p, b-p) <= 0;
}

bool onSegment(P a, P b, P p) {
  return orient(a,b,p) == 0 && inDisk(a,b,p);
}

bool properInter(P a, P b, P c, P d, P &out) {
  double oa = orient(c,d,a),
         ob = orient(c,d,b),
         oc = orient(a,b,c),
         od = orient(a,b,d);
  if (oa*ob < 0 && oc*od < 0) {
    out = (a*ob - b*oa) / (ob-oa);
    return true;
  }
  return false;
}

struct cmpX {
  bool operator()(P a, P b) const {
    return make_pair(a.x, a.y) < make_pair(b.x, b.y);
  }
};

set<P,cmpX> inters(P a, P b, P c, P d) {
  P out;
  if (properInter(a,b,c,d,out)) return {out};
  set<P,cmpX> s;
  if (onSegment(c,d,a)) s.insert(a);
  if (onSegment(c,d,b)) s.insert(b);
  if (onSegment(a,b,c)) s.insert(c);
  if (onSegment(a,b,d)) s.insert(d);
  return s;
}

double segPoint(P a, P b, P p) {
  if (a != b) {
    L l(a,b);
    if (l.cmpProj(a,p) && l.cmpProj(p,b)) // if closest to
      return l.dist(p); // output distance to
  }
  return min(abs(p-a), abs(p-b)); // otherwise distance to A or B
}

double segSeg(P a, P b, P c, P d) {
  P dummy;
  if (properInter(a,b,c,d,dummy))
    return 0;
  return min({segPoint(a,b,c), segPoint(a,b,d),
      segPoint(c,d,a), segPoint(c,d,b)});
}
