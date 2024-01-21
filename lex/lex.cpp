#include <bits/stdc++.h>

using namespace std;

int n,q;
string s;

int pref_ord[300007][20];
int t_order[300000];
int lvl = 0;
int prevpow = 0;

bool comp(const int& a, const int& b) {
    if(lvl == 0) {
        return s[a] < s[b];
    }
    else {
        if(pref_ord[a][lvl - 1] != pref_ord[b][lvl - 1]) {
            return pref_ord[a][lvl - 1] < pref_ord[b][lvl - 1];
        }
        else {
            return pref_ord[a + prevpow][lvl - 1] < pref_ord[b + prevpow][lvl - 1];
        }
    }
}

void count_ord() {
    int cur_pow = 1;
    int sz = 1;
    int cnt = 0;
    while(sz < n) {
        sz*=2;
        cnt++;
    }
    for(int i = 0; i < cnt; i++) {
        lvl = i;
        prevpow = (i > 0) ? pow(2,i-1) : 0; 
        for(int j = 0; j <= n - cur_pow; j++) {
            t_order[j] = j;
        }
        sort(t_order, t_order + n - cur_pow + 1, comp);
        int cur_val = 1;
        pref_ord[t_order[0]][i] = cur_val;
        for(int j = 1; j <= n - cur_pow; j++) {
            if(comp(t_order[j], t_order[j-1]) == 0 && comp(t_order[j-1], t_order[j]) == 0) {
                pref_ord[t_order[j]][i] = cur_val;
            }
            else {
                cur_val++;
                pref_ord[t_order[j]][i] = cur_val;
            }
        }
        cur_pow*=2;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>q;
    cin>>s;
    count_ord();

    int al, ar, bl, br;
    int max_pow = 1;
    int max_cnt = 0;
    for(int i = 0; i < q; i++) {
        cin>>al>>ar>>bl>>br;
        max_pow = 1;
        max_cnt = 0;
        while(max_pow*2 < min(ar - al + 1, br - bl + 1)) {
            max_pow*=2;
            max_cnt++;
        }
        int dist = ((ar - al < br - bl ) ? ar - al : br - bl) + 1 - max_pow;
        if(pref_ord[al - 1][max_cnt] < pref_ord[bl - 1][max_cnt]) {
            cout<<"<"<<endl;
        }
        else if(pref_ord[al - 1][max_cnt] > pref_ord[bl - 1][max_cnt]) {
            cout<<">"<<endl;
        }
        else {
            if(pref_ord[al + dist - 1][max_cnt] < pref_ord[bl + dist - 1][max_cnt]) {
                cout<<"<"<<endl;
            }
            else if(pref_ord[al + dist - 1][max_cnt] > pref_ord[bl + dist - 1][max_cnt]) {
                cout<<">"<<endl;
            }
            else {
                if(ar - al + 1 < br - bl + 1) {
                    cout<<"<"<<endl;
                }
                else if(ar - al + 1 == br - bl + 1){
                    cout<<"="<<endl;
                }
                else {
                    cout<<">"<<endl;
                }
            }
        }
    }
    return 0;
}