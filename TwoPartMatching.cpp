#include <bits/stdc++.h>

using namespace std;

struct edge{
  int to, rev, cap;
};
int n, m;

vector<vector<edge>> G;
vector<bool> used;

int dfs(int v, int t, int f){
  if(v == t) {
    return f;
  }
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

int main() {
  cin >> n >> m;
  G.resize(n + m + 2);
  used.resize(n + m + 2);
  int q;
  cin >> q;
  for(int i = 0; i < q; i++){
    int u, v;
    cin >> u >> v;
    v += n;
    G[u].push_back((edge){v, (int)G[v].size(), 1});
    G[v].push_back((edge){u, (int)G[u].size() - 1, 0});
  }
  // 前半部分と始点を結ぶ
  for(int i = 1; i <= n; i++){
    G[0].push_back((edge){i, (int)G[i].size(), 1});
    G[i].push_back((edge){0, (int)G[0].size() - 1, 0});
  }
  // 後半部分と終点を結ぶ
  for(int i = n + 1; i <= n + m; i++){
    G[i].push_back((edge){n + m + 1, (int)G[n + m + 1].size(), 1});
    G[n + m + 1].push_back((edge){i, (int)G[i].size() - 1, 0});
  }
  int ans = 0;
  while(true){
    used = vector<bool> (n + m + 2, false);
    int f = dfs(0, n + m + 1, 1e8);
    if(f == 0) break;
    ans += f;
  }
  cout << ans << endl;
  return 0;
}