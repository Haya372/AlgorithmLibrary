#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> P;

/* 1. オイラーツアー 
  * ノードaとbの共通祖先(LCA)とその深さを高速に求める
*/
struct RMQ_Euler_Tour{
    private:
    vector<P> dat;
    P INF;
    int n;
    P eval(P a, P b){
      if(a.second < b.second) return a;
      return b;
    }
    //////
    /*
    節点kと範囲[l, r)について
    1. [l, r)と[a, b)の共通部分がなければINFを返す
    2. [l, r)が[a, b)に完全に含まれていればdat[k]を返す
    3. 区間[l, r)を半分に分けて再帰して最小値を求めそのうちの小さい方の値を返す
    */
    //////
    P subQuery(int a, int b, int k, int l, int r){
        if(r <= a || b <= l){ return INF; }  // 1

        if(a <= l && r <= b){ return dat[k]; }  // 2
        else{
            P vl = subQuery(a, b, k * 2 + 1, l, (l + r) / 2);
            P vr = subQuery(a, b, k * 2 + 2, (l + r) / 2, r);
            return eval(vl, vr); // 3
        }
    }
    public:
    void init(int n_){
        n = 1;
        while(n < n_) n *= 2;
        INF = make_pair(-1, numeric_limits<int>::max());
        dat = vector<P>(2 * n - 1, INF);
    }
    //k番目の値を更新
    void update(int k, P a){
        k += n - 1;
        dat[k] = a;
        while(k > 0){
            k = (k - 1) / 2;
            dat[k] = eval(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }
    //[a, b)の最小値を求める
    P query(int a, int b){
        return subQuery(a, b, 0, 0, n);
    }
};

class Euler_tour
{
private:
  vector<P> euler_tour;
  vector<int> depth, first_appear;
  vector<vector<int>> tree;
  RMQ_Euler_Tour rmq;

  void dfs_sub(int now, int d){
    first_appear[now] = euler_tour.size();
    euler_tour.push_back(make_pair(now, d));
    depth[now] = d;
    for(int i = 0; i < tree[now].size(); i++){
      if(depth[tree[now][i]] == -1) {
        dfs_sub(tree[now][i], d + 1);
        euler_tour.push_back(make_pair(now, d));
      }
    }
  }
public:
  Euler_tour(int n_){
    depth = vector<int> (n_, -1);
    first_appear.resize(n_);
    tree.resize(n_);
  }
  // ノードaとノードbをつなぐ
  void connect_node(int a, int b){
    tree[a].push_back(b);
    tree[b].push_back(a);
  }
  // ノードparentからのdepthを求める
  void dfs(int parent){
    dfs_sub(parent, 0);
    rmq.init(euler_tour.size());
    for(int i = 0; i < euler_tour.size(); i++){
      rmq.update(i, euler_tour[i]);
    }
  }
  // ノードaとノードbのLCAを求める。
  // first: index, second: depth
  P calc_LCA(int a, int b){
    int x = first_appear[a], y = first_appear[b];
    if(x > y) swap(x, y);
    return rmq.query(x, y);
  }
  // ノードxのdepthを求める
  int get_depth(int x){
    return depth[x];
  }
};



/* 2. オイラーツアー別バージョン 
  * 深さdのノードのうち、祖先にxを持つものを高速に求める
*/
class Euler_tour2
{
private:
  vector<int> depth, in, out;
  vector<vector<int>> tree, depth_list;
  int time;

  void dfs_sub(int now, int d){
    in[now] = time;
    depth_list[d].push_back(time);
    time++;
    depth[now] = d;
    for(int i = 0; i < tree[now].size(); i++){
      if(depth[tree[now][i]] == -1) {
        dfs_sub(tree[now][i], d + 1);
      }
    }
    out[now] = time;
    time++;
  }
public:
  Euler_tour2(int n_){
    depth = vector<int> (n_, -1);
    in.resize(n_);
    out.resize(n_);
    time = 0;
    tree.resize(n_);
    depth_list.resize(n_);
  }
  // ノードaとノードbをつなぐ
  void connect_node(int a, int b){
    tree[a].push_back(b);
    tree[b].push_back(a);
  }
  // ノードparentからのdepthを求める
  void dfs(int parent){
    dfs_sub(parent, 0);
  }
  // ノードxを祖先に持つ深さdのノードの個数を求める
  int query(int x, int d){
    return lower_bound(depth_list[d].begin(), depth_list[d].end(), out[x]) - lower_bound(depth_list[d].begin(), depth_list[d].end(), in[x]);
  }
  // ノードxのdepthを求める
  int get_depth(int x){
    return depth[x];
  }
};

int main(){
  
  return 0;
}