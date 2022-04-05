#include <bits/stdc++.h>

using namespace std;

// n以下のnと互いに素な数の個数（オイラー関数の値）を返す
int euler_phi(int n){
  int res = n;
  for(int i = 2; i * i <= n; i++){
    if(n % i == 0){
      res = res / i * (i - 1);
      while(n % i == 0) {
        n /= i;
      }
    }
  }
  return res;
}

// オイラー関数の値のリストを返す
vector<int> euler_phi_list(int n){
  vector<int> res(n + 1);
  for(int i = 0; i <= n; i++) res[i] = i;
  for(int i = 2; i <= n; i++){
    if(res[i] == i){
      for(int j = i; j <= n; j += i){
        res[j] = res[j] / i * (i - 1);
      }
    }
  }
  return res;
} 