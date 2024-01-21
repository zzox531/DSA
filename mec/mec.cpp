#include <bits/stdc++.h>

using namespace std;

int n;
short m;
long long prod[40001];
long long cur = 1;

set<long long> same;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    int num;
    for(short i=0; i<m; i++){
        for(int j = 0; j<n; j++){
            cin>>num;
            if(j < n/2) prod[num] ^= cur;
        }
        cur<<=1;
    }
    for(int i = 1; i<=n; i++){
        if(same.find(prod[i]) != same.end()){
            cout<<"NIE"<<endl;
            return 0;
        }
        same.insert(prod[i]);
    }
    cout<<"TAK"<<endl;
    return 0;
}