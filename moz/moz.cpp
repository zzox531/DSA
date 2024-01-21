#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000000

int n,k;
int m;
int dp[3][10007];
int tab[10007];
int res[10007];

void solve(){
    for(int i = 0; i <= k; i++){
        dp[1][i] = 1;
    }
    res[1] = k + 1;
    for(int i = 2; i <= m; i++){
        dp[i % 2][0] = (dp[(i + 1) % 2][0] + dp[(i + 1) % 2][1]) % MOD;
        res[i] += dp[i % 2][0];
        res[i] %= MOD;
        for(int j = 1; j <= k - 1; j++){
            dp[i % 2][j] = ((dp[(i + 1) % 2][j-1] + dp[(i + 1) % 2][j]) % MOD + dp[(i + 1) % 2][j + 1]) % MOD;
            res[i] += dp[i % 2][j];
            res[i] %= MOD;
        }
        dp[i % 2][k] = (dp[(i + 1) % 2][k] + dp[(i + 1) % 2][k - 1]) % MOD;
        res[i] += dp[i % 2][k];
        res[i] %= MOD;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>k;
    for(int i = 0; i < n; i++){
        cin>>tab[i];
        m = max(m, tab[i]);
    }
    solve();
    for(int i = 0; i < n; i++){
        cout<<res[tab[i]]<<" ";
    }
    return 0;
}