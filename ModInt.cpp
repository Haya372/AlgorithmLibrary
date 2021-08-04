#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;

struct ModInt{
    ll n;
    ModInt(ll n_){
        n = n_ % mod;
    }
    ModInt inv(ModInt a){
        ModInt res = ModInt(1);
        ll b = mod - 2;
        while(b > 0){
            if(b & 1) res = res * a;
            a = a * a;
            b >>= 1;
        }
        return res;
    }
    ModInt operator+(ModInt b){
        return ModInt(n + b.n);
    }
    ModInt operator+(ll b){
        return ModInt(n + b);
    }
    void operator+=(ModInt b){
        n = (n + b.n) % mod;
    }
    void operator+=(ll b){
        n = (n + b) % mod;
    }
    ModInt operator-(ModInt b){
        ll c = (n - b.n) % mod;
        if(c < 0) c += mod;
        return ModInt(c);
    }
    ModInt operator-(ll b){
        ll c = (n - b) % mod;
        if(c < 0) c += mod;
        return ModInt(c);
    }
    void operator-=(ModInt b){
        n = (n - b.n) % mod;
        if(n < 0) n += mod;
    }
    void operator-=(ll b){
        n = (n - b) % mod;
        if(n < 0) n += mod;
    }
    ModInt operator*(ModInt b){
        return ModInt(n * b.n);
    }
    ModInt operator*(ll b){
        return ModInt(n * b);
    }
    void operator*=(ModInt b){
        n = n * b.n % mod;
    }
    void operator*=(ll b){
        n = n * b % mod;
    }
    ModInt operator/(ModInt b){
        ModInt div = inv(b);
        return ModInt(n * div.n);
    }
    ModInt operator/(ll b){
        ModInt div = inv(ModInt(b));
        return ModInt(n * div.n);
    }
    void operator/=(ModInt b){
        ModInt div = inv(b);
        n = n * div.n % mod;
    }
    void operator/=(ll b){
        ModInt div = inv(ModInt(b));
        n = n * div.n % mod;
    }
    void operator=(ll b){
        n = b % mod;
    }
};