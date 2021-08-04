#include <bits/stdc++.h>

using namespace std;

double ESP = 1e-10;

// 誤差を考慮した足し算
double add(double a, double b){
  if(abs(a + b) < ESP * (abs(a) + abs(b))) return 0;
  return a + b;
}

struct Vec2d {
  double x, y;
  Vec2d() {}
  Vec2d(double x, double y) : x(x), y(y){}
  Vec2d operator + (Vec2d v){
    return Vec2d(add(x, v.x), add(y, v.y));
  }
  Vec2d operator - (Vec2d v){
    return Vec2d(add(x, -v.x), add(y, -v.y));
  }
  Vec2d operator * (double v){
    return Vec2d(x * v, y * v);
  }
  // 内積
  double dot(Vec2d v){
    return add(x * v.x, y * v.y);
  }
  // 外積
  double det(Vec2d v){
    return add(x * v.y, -y * v.x);
  }
};

// p1-p2上にqがあるか
bool on_seg(Vec2d p1, Vec2d p2, Vec2d q){
  // 直線上にある && 線分に乗っている
  return (p1 - q).det(p2 - q) == 0 && (p1 - q).dot(p2 - q) <= 0;
}

// 直線p1-p2と直線q1-q2の交点
Vec2d intersection(Vec2d p1, Vec2d p2, Vec2d q1, Vec2d q2){
  return p1 + (p2 - p1) * ((q2 - q1).det(q1 - p1) / (q2 - q1).det(p2 - p1));
}

bool comp_Vec2(const Vec2d& p, const Vec2d& q){
  if(p.x != q.x) return p.x < q.x;
  return p.y < q.y;
}

// 凸包を求める
vector<Vec2d> convex_hull(vector<Vec2d> ps){
  int n = ps.size();
  sort(ps.begin(), ps.end(), comp_Vec2);
  int k = 0;
  vector<Vec2d> qs(n * n);
  // 下側の凸包
  for(int i = 0; i < n; i++){
    while(k > 1 && (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0) k--;
    qs[k++] = ps[i];
  }
  // 上側の凸包
  for(int i = n - 2, t = k; i >= 0; i--){
    while(k > t && (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0) k--;
    qs[k++] = ps[i];
  }
  qs.resize(k - 1);
  return qs;
}

double dist(Vec2d p, Vec2d q){
  return (p - q).dot(p - q);
}