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
