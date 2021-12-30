#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> P;

class MinCostFlow{
  struct edge { int to, cap, cost, rev; };
  vector<vector<edge>> G;
  const int INF = 1e8;
  vector<int> h; // ポテンシャル＝残余グラフにおけるスタートからの最短経路
  vector<int> dist; // 最短距離（ダイクストラ法に用いる)
  vector<int> prevv, preve; // 直前の頂点と辺
  int V;

  public:
  MinCostFlow(int n){
    V = n;
    G.resize(n);
    prevv.resize(n);
    preve.resize(n);
  }

  void add_edge(int from, int to, int cap, int cost){
    G[from].push_back((edge){ to, cap, cost, (int)G[to].size() });
    G[to].push_back((edge){ from, 0, -cost, (int)G[from].size() - 1 });
  }

  // s: 始点ノード, t: 終点ノード, f: 流したい流量
  int min_cost_flow(int s, int t, int f){
    int res = 0;
    h = vector<int> (V, 0);
    while(f > 0){
      priority_queue<P, vector<P>, greater<P>> que;
      dist = vector<int> (V, INF);
      dist[s] = 0;
      que.push(make_pair(0, s));
      while(!que.empty()){
        P now = que.top(); que.pop();
        int v = now.second;
        int cost = now.first;
        if(dist[v] < cost) continue;
        for(int i = 0; i < G[v].size(); i++){
          edge &e = G[v][i];
          if(e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]){
            dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
            prevv[e.to] = v;
            preve[e.to] = i;
            que.push(make_pair(dist[e.to], e.to));
          }
        }
      }
      if(dist[t] == INF){
        // これ以上流せない状態
        return -1;
      }
      for(int i = 0; i < V; i ++) h[i] += dist[i];

      // 見つかった最短経路に流せるだけ流す
      int d = f;
      for(int v = t; v != s; v = prevv[v]){
        d = min(d, G[prevv[v]][preve[v]].cap);
      }
      f -= d;
      res += d * h[t];
      for(int v = t; v != s; v = prevv[v]){
        edge &e = G[prevv[v]][preve[v]];
        e.cap -= d;
        G[v][e.rev].cap += d;
      }
    }
    return res;
  }
};