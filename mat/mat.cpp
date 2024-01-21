#include <bits/stdc++.h>

using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    string s;
    cin>>s;
    int min_len = s.size();
    int p = 0;
    int q = 1;
    while(q<s.size()){
        if(s[q]==s[p] || s[q]!=s[p] && s[p]=='*'){
            p=q;
        }
        else if(s[q] != s[p] && s[q]!='*'){
            min_len=min(min_len,q-p);
            p=q;
        }
        q++;
    }
    cout<<s.size()-min_len+1<<endl;
    return 0;
}