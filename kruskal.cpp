#include<bits/stdc++.h>

using namespace std;

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
};

struct edge{ int u, v, cost; };

bool comp(const edge& e1, const edge& e2){
    return e1.cost < e2.cost;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<edge>es(m);
    for(int i = 0; i < m; i++){
        int a, b, c;
        cin >> a >> b >> c;
        edge e = {a, b, c};
        es[i] = e;
    }
    UnionFind uf(n);
    sort(es.begin(), es.end(), comp);
    int ans = 0;
    for(int i = 0; i < m; i++){
        edge e = es[i];
        if(!uf.same(e.u, e.v)){
            uf.unite(e.v, e.u);
            ans += e.cost;
        }
    }
    return 0;
}