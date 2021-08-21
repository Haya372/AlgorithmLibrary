#include <bits/stdc++.h>

using namespace std;

vector<int> prime_generator(int n){
  vector<int> res;
  vector<bool> isPrime(n + 1, true);
  for(int i = 2; i <= n; i++){
    if(!isPrime[i]) continue;
    res.push_back(i);
    for(int j = i * 2; j <= n; j += i){
      isPrime[j] = false;
    }
  }
  return res;
}

class PrimeFactrization{
  vector<int> pf;
  vector<bool> isPrime;
  public:
  PrimeFactrization(int n){
    pf.resize(n + 1);
    isPrime.resize(n + 1, true);
    for(int i = 2; i <= n; i++){
      if(!isPrime[i]) continue;
      pf[i] = i;
      for(int j = i * 2; j <= n; j += i){
        isPrime[j] = false;
        pf[j] = i;
      }
    }
  }
  vector<int> get_primes(int n){
    vector<int> res;
    while(n != 1){
      res.push_back(pf[n]);
      n /= pf[n];
    }
    sort(res.begin(), res.end());
    return res;
  }
};