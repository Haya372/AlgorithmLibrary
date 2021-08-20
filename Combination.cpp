#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;

class Comb {
  vector<ll> kaizyou;
  Comb(int n_) {
    kaizyou.resize(n_ + 1);
    kaizyou[0] = 1;
    for(int i = 1; i < kaizyou.size(); i++){
      kaizyou[i] = i * kaizyou[i - 1] % mod;
    }
  }
  // x^nを求める
  ll pow(ll x, ll n){
    ll res = 1;
    while(n > 0){
      if(n & 1) {
        res *= x;
        res %= mod;
      }
      x *= x;
      x %= mod;
      n >>= 1;
    }
    return res;
  }
  // nCkを求める
  ll calc(ll n, ll k){
    if(n < k) return 0;
    ll res = kaizyou[n] * this -> pow(kaizyou[n - k], mod - 2) % mod;
    res *= this -> pow(kaizyou[k], mod - 2);
    res %= mod;
    return res;
  }
  // x!を求める
  ll calc_kaizyou(ll x){
    return kaizyou[x];
  }
};