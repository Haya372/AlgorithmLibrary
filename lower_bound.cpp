#include <bits/stdc++.h>

using namespace std;

int lower_bound(int v, vector<int> a){
    int l = 0, r = a.size() - 1;
    while(r - l > 1){
        int middle = (l + r) / 2;
        if(a[middle] >= v) r = middle;
        else l = middle;
    }
    return r;
}

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int k;
    cin >> k;
    cout << lower_bound(k, a) << endl;
    return 0;
}