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

