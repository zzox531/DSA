#include <bits/stdc++.h>

using namespace std;

int n,m,k;
int needed[100007];
int vis[100007];
vector<int>* g;

void dfs(int w) {
    vis[w] = true;
    for(int i = 0; i < g[w].size(); i++) {
        if(!vis[g[w][i]]){
            dfs(g[w][i]);
        }
        needed[w] = max(needed[w], needed[g[w][i]]);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m>>k;
    g = new vector<int>[n + 1];
    for(int i = 0; i < n; i++) {
        cin>>needed[i];
    }

    int num1, num2;

    for(int i = 0; i < m; i++) {
        cin>>num1>>num2;
        g[num1 - 1].push_back(num2 - 1);
    }

    for(int i = 0; i < n; i++) {
        if(vis[i] == false) {
            dfs(i);
        }
    }

    sort(needed, needed + n);
    cout<<needed[k - 1]<<endl;

    return 0;
}