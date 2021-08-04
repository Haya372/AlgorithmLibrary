#include<bits/stdc++.h>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector< vector<int> >g(n);
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<int>node(n);
    int ans = true;
    stack<int>todo;
    for(int i = 0; i < n; i++){
        if(node[i] != 0)continue;
        node[i] = 1;
        todo.push(i);
        while(todo.empty() != 1){
            int p = todo.top();
            todo.pop();
            int nextcolor = node[p] == 1 ? 2 : 1; 
            for(int next: g[p]){
                if(node[next] == 0){
                    node[next] = nextcolor;
                    todo.push(next);
                } else{
                    if(node[next] != nextcolor){
                        ans = false;
                        break;
                    }
                }
            }
            if(!ans) break;
        }
        if(!ans) break;
    }
    if(ans){
        cout << "Yes" << endl;
    }else{
        cout << "No" << endl;
    }
    return 0;
}