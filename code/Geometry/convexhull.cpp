struct pt{
double x,y;
};

bool cmp(pt a, pt b) {
  return a.x < b.x || (a.x==b.x && a.y<b.y);
}

bool cw(pt a, pt b, pt c) {
  return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y)<0;
}

bool ccw(pt a, pt b, pt c) {
  return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y)>0;
}

vector<pt> convex_hull(vector<pt>&a) { // return in clockwise order
  if(a.size()==1) return a;
  sort(a.begin(), a.end(), &cmp);
  pt p1=a[0], p2=a.back();
  vector<pt>up,down;
  PRE(i,0,a.size(),1) {
      while(up.size() >= 2 && !cw(up[up.size()-2], up[up.size()-1], a[i])) up.pop_back();
      up.push_back(a[i]);
      while(down.size() >= 2 && !ccw(down[down.size()-2], down[down.size()-1], a[i])) down.pop_back();
      down.push_back(a[i]);
  }
  vector<pt>res;
  PRE(i,1,down.size()-1,1) {
    if(res.size() == 0 || (res.size() > 0 && !(down[i].x == res[res.size()-1].x && down[i].y==res[res.size()-1].y))) {
    res.push_back(down[i]);
    }
  }
  RPRE(i,up.size()-1,0,1) {
    if(res.size() == 0 || (res.size() > 0 && !(up[i].x == res[res.size()-1].x && up[i].y==res[res.size()-1].y))) {
    res.push_back(up[i]);
    }
  }
  return res;
}
