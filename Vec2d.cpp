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

int main(){
  int n;
  cin >> n;
  vector<Vec2d> p(n), q(n);
  for(int i = 0; i < n; i++){
    double x, y;
    cin >> x >> y;
    p[i] = Vec2d(x, y);
  }
  for(int i = 0; i < n; i++){
    int x, y;
    cin >> x >> y;
    q[i] = Vec2d(x, y);
  }
  int m;
  cin >> m;
  vector<int> a(m), b(m);
  for(int i = 0; i < m; i++){
    cin >> a[i] >> b[i];
    a[i]--; b[i]--;
  }
  vector<vector<bool>> G(n, vector<bool>(n));
  for(int i = 0; i < n; i++){
    G[i][i] = true;
    for(int j = i + 1; j < n; j++){
      if((p[i] - q[i]).det(p[j] - q[j]) == 0){
        G[i][j] = G[j][i] = on_seg(p[i], q[i], p[j])
                          || on_seg(p[i], q[i], q[j])
                          || on_seg(p[j], q[j], p[i])
                          || on_seg(p[j], q[j], q[i]);
      }else{
        Vec2d r = intersection(p[i], q[i], p[j], q[j]);
        G[i][j] = G[j][i] = on_seg(p[i], q[i], r) && on_seg(p[j], q[j], r);
      }
    }
  }
  for(int k = 0; k < n; k++){
    for(int i = 0; i < n; i++){
      for(int j = 0; j < n; j++){
        G[i][j] = G[i][j] | (G[i][k] && G[k][j]);
      }
    }
  }
  for(int i = 0; i < m; i++){
    if(G[a[i]][b[i]]) cout << "CONNECTED" << endl;
    else cout << "NOT CONNECTED" << endl;
  }
  return 0;
}