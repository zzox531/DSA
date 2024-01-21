#include <bits/stdc++.h>

using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin>>n;

    int tab[n+2];
    int left_odd[n+2];
    int left_even[n+2];
    int right_odd[n+2];
    int right_even[n+2];
    long long right_suff[n+2];
    
    left_odd[0] = -1;
    left_even[0] = -1;
    right_odd[n+1] = -1;
    right_even[n+1] = -1;
    right_suff[n+1] = 0;

    for(int i=1; i<=n; i++){
        cin>>tab[i];
        if(tab[i]%2==1){
            left_odd[i] = i;
            left_even[i] = left_even[i-1];
        }
        else {
            left_odd[i] = left_odd[i-1];
            left_even[i] = i;
        }
    }

    for(int i=n; i>=0; i--){
        right_suff[i] = right_suff[i+1] + tab[i];
        if(tab[i]%2==1){
            right_odd[i] = i;
            right_even[i] = right_even[i+1];
        }
        else{
            right_odd[i] = right_odd[i+1];
            right_even[i] = i;
        }
    }

    int q;
    cin>>q;

    int num;

    long long val1=-1;
    long long val2=-1;

    for(int i=0; i<q; i++){
        cin>>num;
        val1=-1;
        val2=-1;
        if(right_suff[n-num+1]%2==1){
            cout<<right_suff[n-num+1]<<endl;
        }
        else{
            if(left_odd[n-num] != -1 && right_even[n-num+1] != -1){
                val1 = right_suff[n-num+1] - (long long)tab[right_even[n-num+1]] + (long long)tab[left_odd[n-num]];
            }
            if(left_even[n-num] != -1 && right_odd[n-num+1] != -1){
                val2 = right_suff[n-num+1] - (long long)tab[right_odd[n-num+1]] + (long long)tab[left_even[n-num]];
            }
            if(val1 == -1 && val2 == -1){
                cout<<"-1"<<endl;
            }
            else{
                cout<<max(val1,val2)<<endl;
            }
        }
    }

    return 0;
}