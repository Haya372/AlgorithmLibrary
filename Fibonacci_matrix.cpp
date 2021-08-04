#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll mod = 1e4;

vector<vector<ll>> mul(vector<vector<ll>> mtx1, vector<vector<ll>> mtx2){
  int n = mtx1.size();
  vector<vector<ll>> res(n, vector<ll> (n));
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      for(int k = 0; k < n; k++){
        res[j][i] += mtx1[j][k] * mtx2[k][i] % mod;
        res[j][i] %= mod;
      }
    }
  }
  return res;
}

vector<vector<ll>> pow_mtx(vector<vector<ll>> mtx, ll x) {
  int n = mtx.size();
  vector<vector<ll>> res = {
    {1, 0},
    {0, 1}
  };
  while(x > 0){
    if(x & 1) res = mul(res, mtx);
    mtx = mul(mtx, mtx);
    x >>= 1;
  }
  return res;
}

int main(){
  ll n;
  cin >> n;
  vector<vector<ll>> mtx = {
    {1, 1},
    {1, 0}
  };
  if(n == 0) return 0;
  n--;
  mtx = pow_mtx(mtx, n);
  for(int i = 0; i < 2; i++){
    for(int j = 0; j < 2; j++){
      cout << mtx[i][j] << " " ;
    }
    cout << endl;
  }
  cout << mtx[0][0] * 1 % mod<< endl;
  return 0;
}