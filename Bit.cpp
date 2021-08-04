#include <bits/stdc++.h>

using namespace std;

template<class T>
class BIT{
  private:
  int n;
  vector<T> bit;
  public:
  BIT(int n_){
    n = n_;
    bit = vector<T>(n + 1);
  }
  T sum(int i){
    T s = 0;
    while(i > 0){
      s += bit[i];
      i -= i & -i;
    }
    return s;
  }
  void add(int i, T x){
    while(i <= n){
      bit[i] += x;
      i += i & -i;
    }
  }
};