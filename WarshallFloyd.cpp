#include<bits/stdc++.h>

using namespace std;

const int INF = 1e8;

int main(){
    int n, m;
    cin >> n >> m;
    vector< vector<int> >d(n, vector<int>(n, INF));
    for(int k = 0; k < n; k ++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}