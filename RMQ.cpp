#include <bits/stdc++.h>

using namespace std;


template<class type>
class RMQ{
  private:
  vector<type> dat;
  type INF;
  int n;
  //////
  /*
  節点kと範囲[l, r)について
  1. [l, r)と[a, b)の共通部分がなければINFを返す
  2. [l, r)が[a, b)に完全に含まれていればdat[k]を返す
  3. 区間[l, r)を半分に分けて再帰して最小値を求めそのうちの小さい方の値を返す
  */
  //////
  type subQuery(int a, int b, int k, int l, int r){
    if(r <= a || b <= l){ return INF; }  // 1

    if(a <= l && r <= b){ return dat[k]; }  // 2
    else{
      type vl = subQuery(a, b, k * 2 + 1, l, (l + r) / 2);
      type vr = subQuery(a, b, k * 2 + 2, (l + r) / 2, r);
      return min(vl, vr); // 3
    }
  }
  public:
  RMQ(int n_){
    n = 1;
    while(n < n_) n *= 2;
    INF = numeric_limits<type>::max();
    dat = vector<type>(2 * n - 1, INF);
  }
  //k番目の値を更新
  void update(int k, type a){
    k += n - 1;
    dat[k] = a;
    while(k > 0){
      k = (k - 1) / 2;
      dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
    }
  }
  //[a, b)の最小値を求める
  type query(int a, int b){
    return subQuery(a, b, 0, 0, n);
  }
};

int main(){
    int n;
    cin >> n;
    RMQ<int> rmq = RMQ<int>(n);
    for(int i = 0; i < n; i++){
        int t;
        cin >> t;
        rmq.update(i, t);
    }
    cout << "[0, n) : " << rmq.query(0, n) << endl;
    cout << "[0, n / 2) : " << rmq.query(0, n / 2) << endl;
    cout << "[1, n - 1) : " << rmq.query(1, n - 1) << endl;
    return 0;
}