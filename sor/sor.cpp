#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000000

int n;
int tab[1007];
int dp[1007][1007][2];

void solve(){
    for(int i=0; i<n; i++){
        dp[i][i][1] = 1;
    }
    int range = 1;
    int j;
    while(range < n){
        for(int i = 0; i<n-range; i++){
            j = i + range;
            if(tab[j] > tab[j-1]){
                dp[i][j][1] += dp[i][j-1][1];
                dp[i][j][1] %= MOD;
            }
            if(tab[j] > tab[i]){
                dp[i][j][1] += dp[i][j-1][0];
                dp[i][j][1] %= MOD;
            }
            if(tab[i] < tab[i+1]){
                dp[i][j][0] += dp[i+1][j][0];
                dp[i][j][0] %= MOD;
            }
            if(tab[i] < tab[j]){
                dp[i][j][0] += dp[i+1][j][1];
                dp[i][j][0] %= MOD;
            }
        }
        range++;
    }

}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>n;
    for(int i=0; i<n; i++){
        cin>>tab[i];
    }
    solve();
    cout<<(dp[0][n-1][0] + dp[0][n-1][1])%MOD<<endl;
    return 0;
}