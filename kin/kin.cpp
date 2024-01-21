#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000000

int n,k;
int tab[20007];
int dp[20007];
int tree[65537];
int ret = 0;
int sz = 1;

int query(int w, int p, int q, int a, int b){
    if(b < a) return 0;
    if(p >= a && q <= b) return tree[w];
    else if(p > b || q < a) return 0;
    else return (query(w * 2, p, (p + q) / 2, a, b) + query(w * 2 + 1, (p + q) / 2 + 1, q, a, b)) % MOD;
}

void update(int w){
    if(w < sz) tree[w] = (tree[w*2] + tree[w*2+1])%MOD;
    if(w > 1) update(w/2); 
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>k;
    while(sz < n) sz*=2;
    for(int i = 0; i < n; i++){
        cin>>tab[i];
        dp[i] = 1;
    }
    for(int i = 2; i<=k; i++){
        for(int j = 1; j<2*sz; j++) tree[j] = 0; 
        for(int j = n-1; j>=0; j--){
            tree[sz + tab[j] - 1] = dp[j];
            update(sz + tab[j] - 1);
            dp[j] = query(1, 1, sz, 1, tab[j]-1);
        }
    }
    for(int i = 0; i < n; i++){
        ret = (ret + dp[i])%MOD;
    }
    cout<<ret<<endl;
    return 0;
}