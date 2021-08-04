#include <bits/stdc++.h>

using namespace std;

int calc_triangle(int x1, int y1, int x2, int y2, int x3, int y3){
  x2 -= x1; x3 -= x1;
  y2 -= y1; y3 -= y1;
  return abs(x2 * y3 - x3 * y2);
}


// 以下の線分が交わるかどうか
// (x1, y1) - (x2, y2)
// (x3, y3) - (x4, y4)
bool intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){
  int tmp1 = calc_triangle(x1, y1, x3, y3, x4, y4) + calc_triangle(x2, y2, x3, y3, x4, y4);
  int tmp2 = calc_triangle(x3, y3, x1, y1, x2, y2) + calc_triangle(x4, y4, x1, y1, x2, y2);
  return tmp1 == tmp2;
}

// ２つの円の共有点を求める
bool intersect_circle(double x1, double y1, double r1, double x2, double y2, double r2){
  double dx = x2 - x1, dy = y2 - y1; // 円1を原点に移動
  double a = dx * dx + dy * dy;
  double d = abs((dx * dx + dy * dy + r1 * r1 - r2 * r2) / 2) / sqrt(dx * dx + dy * dy); // 共有点どうしを結ぶ直線と原点の距離
  double c2 = r1 * r1 - d * d; // 共有点の中点から交点までの距離の２乗
  if(c2 < 0) return false; // 共有点を持たない
  double c = sqrt(c2);
  double x3 = x1 + dx * d, y3 = y1 + dy * d; // 共有点の中点の座標
  double x4 = -dx * c, y4 = dy * c; // 交点の中点から共有点までの移動ベクトル
  // 共有点は(x3 + x4, y3 + y4)と(x3 - x4, y3 - y4)の２点になる
  return true;
}