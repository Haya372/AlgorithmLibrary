#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

// 1次絶対値関数の傾きが0になる点とそのときの関数の値を求める
class SlopeTrick{
  private:
  ll v;
  priority_queue<int> L; // 傾き0になるxの値の左側
  priority_queue<int, vector<int>, greater<int>> R; // 傾き0になるxの値の右側
  public:
  SlopeTrick(){
    v = 0;
  }
  // 全体に傾きが正の部分を加算
  // |x - a| + b (x >= a)
  void pushL(int a, int b){
    v += b;
    if(L.size() > 0) v += max(0, L.top() - a);
    L.push(a);
    int l0 = L.top(); L.pop();
    R.push(l0);
  }
  // 全体に傾きが負の部分を加算
  // |x - a| + b (x < a)
  void pushR(int a, int b){
    v += b;
    if(R.size() > 0) v += max(0, a - R.top());
    R.push(a);
    int r0 = R.top(); R.pop();
    L.push(r0);
  }
  // 全体に|x - a| + b を加算
  void push(int a, int b){
    pushL(a, b);
    pushR(a, b);
    v -= b; // 足しすぎた分を引く
  }
  // 最小値をとるxを求める
  int get_minX(){
    return L.top();
  }
  // 最小値を求める
  ll get_min_value(){
    return v;
  }
};