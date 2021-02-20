struct L {
  P ps[2]; P v; T c;
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
  double dist(P p) {return abs(side(p)) / v.abs();}
  double sqDist(P p) {return side(p)*side(p) / (double)v.abs();}
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
