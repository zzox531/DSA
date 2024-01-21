#include <bits/stdc++.h>

using namespace std;

int n,m;
int sz = 1;
int tree[2097155];
int tree_sum[2097155];

void push_down(int w){
    if(w < sz){
        if(tree[w] == -1){
            tree[w * 2] = -1;
            tree[w * 2 + 1] = -1;
            tree_sum[w * 2] = 0;
            tree_sum[w * 2 + 1] = 0;
        }
        else {
            tree[w * 2] = tree[w] / 2;
            tree[w * 2 + 1] = tree[w] / 2;
            tree_sum[w * 2] = tree[w] / 2;
            tree_sum[w * 2 + 1] = tree[w] / 2;
        }
        tree[w] = 0;
    }
}

void update(int w, int p, int q, int a, int b, int val){
    if(p >= a && q <= b) {
        if(val == -1){
            tree[w] = -1;
            tree_sum[w] = 0;
        }
        else {
            tree[w] = (q - p + 1);
            tree_sum[w] = (q - p + 1);
        }
    }
    else if(p > b || q < a) return;
    else{
        if(tree[w] != 0) push_down(w);
        update(w * 2, p, (p + q) / 2, a, b, val);
        update(w * 2 + 1, (p + q) / 2 + 1, q, a, b, val);
        tree_sum[w] = tree_sum[w * 2] + tree_sum[w * 2 + 1];
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    while(sz < n) sz *= 2;
    int num1,num2;
    char c;
    for(int i = 0; i < m; i++){
        cin>>num1>>num2>>c;
        if(c == 'C'){
            update(1, 1, sz, num1, num2, -1);
        }
        else{
            update(1, 1, sz, num1, num2, 1);
        }
        cout<<tree_sum[1]<<endl;
    }
    return 0;
}