#include<bits/stdc++.h>

using namespace std;
/* バグあり
struct UnionFind{
    vector<int> parent;
    vector<int> rank;

    // 初期化
    UnionFind(int n){
        this->parent = vector<int>(n);
        this->rank = vector<int>(n, 0);
        for(int i = 0; i < n; i++){
            this->parent[i] = i;
        }
    }
    // 木の根を求める
    int find(int x){
        if(parent[x] == x){
            return x;
        }else{
            return parent[x] = find(parent[x]);
        }
    }
    // xの属する木とyの属する木を結合する
    void unite(int x, int y){
        int par_x = this->find(x);
        int par_y = this->find(y);
        if(par_x == par_y) return;

        if(rank[x] < rank[y]){
            parent[x] = y;
        }else{
            parent[y] = x;
            if(rank[x] == rank[y])rank[x]++;
        }
    }
    // xとyが同じ集合に属するかどうか
    bool same(int x, int y){
        return find(x) == find(y);
    }
};*/

struct UnionFind {
  vector<int> par; 
  vector<int> size;
  UnionFind(int N) : par(N), size(N, 1) { 
    for(int i = 0; i < N; i++) par[i] = i;
  }
  int root(int x) { 
    if (par[x] == x) return x;
    return par[x] = root(par[x]);
  }
  void unite(int x, int y) { 
    int rx = root(x); 
    int ry = root(y); 
    if (rx == ry) return; 
    par[rx] = ry; 
    size[ry] += size[rx];
  }
  bool same(int x, int y) { 
    int rx = root(x);
    int ry = root(y);
    return rx == ry;
  }
  int size(int x){
    return size[root(x)];
  }
};

int main(){
    int n, k;
    cin >> n >> k;
    vector<int>t(k), x(k), y(k);
    for(int i = 0; i < k; i++){
        cin  >> t[i] >> x[i] >> y[i];
        x[i]--;
        y[i]--;
    } 
    UnionFind uf(n * 3);
    int ans = 0;
    for(int i = 0; i < k ; i++){
        if(x[i] < 0 || x[i] >= 100 || y[i] < 0 || y[i] >= 100){
            ans++;
            continue;
        }
        if(t[i] == 1){
            if(uf.same(x[i], y[i] + n) || uf.same(x[i], y[i] + 2 * n)){
                ans++;
                continue;
            }else{
                uf.unite(x[i], y[i]);
                uf.unite(x[i] + n, y[i] + n);
                uf.unite(x[i] + 2 * n, y[i] + 2 * n);
            }
        }else if(t[i] == 2){
            if(uf.same(x[i], y[i]) || uf.same(x[i], y[i] + 2 * n)){
                ans++;
                continue;
            }else{
                uf.unite(x[i], y[i] + n);
                uf.unite(x[i] + n, y[i] + 2 * n);
                uf.unite(x[i] + 2 * n, y[i]);
            }
        }
    }
    cout << ans << endl;
    return 0;
}