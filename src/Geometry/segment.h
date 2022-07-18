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
