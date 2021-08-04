#include <bits/stdc++.h>

using namespace std;

struct edge{int to, cap, rev;};
const int INF = 1e9;

int n; // 頂点の数

vector<vector<edge>> G;
vector<bool> used;

void add_edge(int from, int to, int cap){
  G[from].push_back((edge) {to, cap, G[to].size()});
  G[to].push_back((edge) {from, 0, G[from].size() - 1});
}

// v : 現在地
// t : 目標地点
// f : そのパスに流すことができる最大の流量
int dfs(int v, int t, int f){
  if(v == t) return f;
  used[v] = true;
  for(int i = 0; i < G[v].size(); i++){
    edge &e = G[v][i];
    if(!used[e.to] && e.cap > 0){
      int d = dfs(e.to, t, min(f, e.cap));
      if(d > 0){
        e.cap -= d;
        G[e.to][e.rev].cap += d;
        return d;
      }
    }
  }
  return 0;
}

int max_flow(int s, int t){
  int flow = 0;
  while(true){
    used = vector<bool> (n, false);
    int f = dfs(s, t, INF);
    if(f == 0) return flow;
    flow += f;
  }
}