#include <bits/stdc++.h>
#define MAX_N 15
using namespace std;

struct edge {
  int to, cost;
};

vector<vector<int>> dp(1 << MAX_N, vector<int> (MAX_N, -1));
int n;
vector<vector<edge>> G(MAX_N);

int bitDP(int s, int v){
  if(dp[s][v] >= 0) {
    return dp[s][v];
  }

  if(s == (1 << n) - 1 && v == 0){
    return dp[s][v] = 0;
  }

  int res = INT_MAX / 100;
  
  for(edge e: G[v]){
    int i = e.to;
    if(!((s >> i) & 1)){
      res = min(res, bitDP(s | (1 << i), i) + e.cost);
    }
  }
  return dp[s][v] = res;
}

int main() {
  cin >> n;
  int m;
  cin >> m;
  for(int i = 0; i < m; i++){
    int x, y, c;
    cin >> x >> y >> c;
    edge e1 = {y, c};
    G[x].push_back(e1);
  }
  cout << bitDP(0, 0) << endl;
  return 0;
}