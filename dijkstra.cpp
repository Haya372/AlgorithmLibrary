#include<bits/stdc++.h>

using namespace std;
using ll = long long;
typedef pair<int, int> P;

const int INF = 1e8;

struct edge {
    int to;
    int cost;
};

class Dijkstra {
  int n;
  vector<vector<P>> G;
  public:
  Dijkstra(int n_) {
    n = n_;
    G.resize(n_);
  }

  void add_edge(int from, int to, int cost){
    G[from].push_back(P(to, cost));
  }

  vector<int> calc(int s){
    priority_queue<P, vector<P>, greater<P>> que;
    vector<int> d(n, INF);
    d[s] = 0;
    que.push(P(0, s));
    vector<bool>used(n, false);
    while(!que.empty()){
      P p = que.top(); que.pop();
      int v = p.second;
      if(d[v] < p.first)continue;
      for(int i = 0; i < G[v].size(); i++){
        P e = G[v][i];
        if(d[e.first] > d[v] + e.second){
          d[e.first] = d[v] + e.second;
          que.push(P(d[e.first], e.first));
        }
      }
    }
    return d;
  }
};

int main(){
    int n, m;
    cin >> n >> m;
    vector< vector<edge> >G(n);
    vector<int>d(n, INF);
    vector<bool>used(n, false);
    for(int i = 0; i < m; i++){
        int a, b, c;
        cin >> a >> b >> c;
        edge e1 = {b, c};
        edge e2 = {a, c};
        G[a].push_back(e1);
        G[b].push_back(e2);
    }
    priority_queue< P, vector<P>, greater<P> > que;
    int s = 0;
    d[s] = 0;
    que.push(P(0, s));
    while(!que.empty()){
        P p = que.top(); que.pop();
        int v = p.second;
        if(d[v] < p.first)continue;
        for(int i = 0; i < G[v].size(); i++){
            edge e = G[v][i];
            if(d[e.to] > d[v] + e.cost){
                d[e.to] = d[v] + e.cost;
                que.push(P(d[e.to], e.to));
            }
        }
    }
    return 0;
}