#include <bits/stdc++.h>

using namespace std;

int gcd(int x, int y){
  if(x < y)swap(x, y);
  if(x % y == 0)return y;
  return gcd(y, x % y);
}

int extgcd(int a, int b, int &x, int &y){
  int d = a;
  if(b != 0){
    d = extgcd(b, a % b, y, x);
    y -= (a / b) * x;
  }else{
    x = 1; y = 0;
  }
  return d;
}