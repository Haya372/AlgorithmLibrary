#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> P;

const int INF = 1e8;

struct edge { int to, cap, cost, rev; };

int V; // 頂点数
// 以下の変数はVの値が確定後、reshape(V)をしておく
vector<int> dist; // 最短距離
vector<int> prevv, preve; // 直前の頂点と辺
vector<vector<edge>> G;

void add_edge(int from, int to, int cap, int cost){
  G[from].push_back((edge){ to, cap, cost, (int)G[to].size() });
  G[to].push_back((edge){ from, 0, -cost, (int)G[from].size() - 1 });
}

// s: 始点ノード, t: 終点ノード, f: 流したい流量
int min_cost_flow(int s, int t, int f){
  int res = 0;
  while(f > 0){
    dist = vector<int> (V, INF);
    dist[s] = 0;
    bool update = true;
    while(update){
      update = false;
      for(int v = 0; v < V; v++){
        if(dist[v] == INF) continue;
        for(int i = 0; i < G[v].size(); i++){
          edge &e = G[v][i];
          if(e.cap > 0 && dist[e.to] > dist[v] + e.cost){
            dist[e.to] = dist[v] + e.cost;
            prevv[e.to] = v;
            preve[e.to] = i;
            update = true;
          }
        }
      }
    }
    if(dist[t] == INF){
      // これ以上流せない状態
      return -1;
    }

    // 見つかった最短経路に流せるだけ流す
    int d = f;
    for(int v = t; v != s; v = prevv[v]){
      d = min(d, G[prevv[v]][preve[v]].cap);
    }
    f -= d;
    res += d * dist[t];
    for(int v = t; v != s; v = prevv[v]){
      edge &e = G[prevv[v]][preve[v]];
      e.cap -= d;
      G[v][e.rev].cap += d;
    }
  }
  return res;
}

void init(){
  G.resize(V);
  prevv.resize(V);
  preve.resize(V);
}