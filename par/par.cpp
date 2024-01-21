#include <bits/stdc++.h>

using namespace std;

int two_len[500007][21];
pair<int,int> furthest_up[500007];
pair<int,int> furthest_down[500007];
pair<int,int> furthest[500007];
int depth[500007];
int lft[500007];
int rgh[500007];
int n;
int m;
int q;

void count_two_len() {
    for (int i = 1; i <= 20; i++) {
        for (int j = 1; j <= n; j++) {
            if (two_len[j][i-1] == -1) {
                two_len[j][i] = -1;
            }
            else {
                two_len[j][i] = two_len[two_len[j][i - 1]][i - 1];
            }
        }
    }
}

void count_depth(int w, int d) {
    depth[w] = d;
    if(lft[w] != -1)
        count_depth(lft[w], d + 1);
    if(rgh[w] != -1)
        count_depth(rgh[w], d + 1);
}

pair<int,int> count_furthest_down(int w) {
    furthest_down[w] = make_pair(w, 0);
    if(lft[w] == -1 && rgh[w] == -1)
        return make_pair(w,0);
    pair<int,int> l_f = make_pair(-1, -1);
    pair<int,int> r_f = make_pair(-1, -1);
    if(lft[w] != -1)
        l_f = count_furthest_down(lft[w]);
    if(rgh[w] != -1)
        r_f = count_furthest_down(rgh[w]);
    if(l_f == make_pair(-1, -1)) {
        furthest_down[w] = make_pair(r_f.first, r_f.second + 1);
        return furthest_down[w];
    }
    else if(r_f == make_pair(-1, -1)){
        furthest_down[w] = make_pair(l_f.first, l_f.second + 1);
        return furthest_down[w];
    }
    else {
        if(l_f.second > r_f.second) {
            furthest_down[w] = make_pair(l_f.first, l_f.second + 1);
            return furthest_down[w];
        }
        else {
            furthest_down[w] = make_pair(r_f.first, r_f.second + 1);
            return furthest_down[w];
        }
    } 
        
}

void count_furthest_up(int w, pair<int,int> fur) {
    furthest_up[w] = fur;

    if(lft[w] != -1) {
        if(rgh[w] == -1 || (rgh[w] != -1 && furthest_up[w].second > furthest_down[rgh[w]].second + 1)) {
            count_furthest_up(lft[w], make_pair(furthest_up[w].first, furthest_up[w].second + 1));
        }
        else {
            count_furthest_up(lft[w], make_pair(furthest_down[rgh[w]].first, furthest_down[rgh[w]].second + 2));
        }
    }
    if(rgh[w] != -1) {
        if(lft[w] == -1 || (lft[w] != -1 && furthest_up[w].second > furthest_down[lft[w]].second + 1)) {
            count_furthest_up(rgh[w], make_pair(furthest_up[w].first, furthest_up[w].second + 1));
        }
        else {
            count_furthest_up(rgh[w], make_pair(furthest_down[lft[w]].first, furthest_down[lft[w]].second + 2));
        }
    }
}

int jump_up(int cur_w, int dist) {
    int jmp_rng = 0;
    while(dist > 0) {
        if(dist % 2 == 1)
            cur_w = two_len[cur_w][jmp_rng];
        dist /= 2;
        jmp_rng++;
    }

    return cur_w;
}

int lca(int w1, int w2) {
    if(depth[w1] > depth[w2])
        w1 = jump_up(w1, depth[w1] - depth[w2]);
    else 
        w2 = jump_up(w2, depth[w2] - depth[w1]);
    if(w1 == w2) return w1;
    int range = 20;
    int q = 1;
    while(range >= 0) {
        if(two_len[w1][range] != -1 && two_len[w1][range] == two_len[w2][range]) {
            q = two_len[w1][range];
        }
        else if(two_len[w1][range] != -1 && two_len[w2][range] != -1 && two_len[w1][range] != two_len[w2][range]) {
            w1 = two_len[w1][range];
            w2 = two_len[w2][range];
        }
        range--;
    }
    return q;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> lft[i] >> rgh[i];
        if(lft[i] != -1)
            two_len[lft[i]][0] = i;
        if(rgh[i] != -1)
            two_len[rgh[i]][0] = i;
    }
    two_len[1][0] = -1;
    count_two_len();
    count_depth(1, 0);
    count_furthest_down(1);
    count_furthest_up(1, make_pair(1, 0));
    cin>>q;
    int num1,num2;
    int anc;
    for(int i = 1; i <= n; i++) {
        if(furthest_up[i].second > furthest_down[i].second) furthest[i] = furthest_up[i];
        else furthest[i] = furthest_down[i];
    }
    for(int i = 0; i < q; i++) {
        cin>>num1>>num2;
        if(num2 > furthest[num1].second) {
            cout<<-1<<endl;
        }
        else {
            anc = lca(num1, furthest[num1].first);
            if(abs(depth[num1] - depth[anc]) >= num2) {
                cout<<jump_up(num1,num2)<<endl;
            }
            else {
                cout<<jump_up(furthest[num1].first, furthest[num1].second - num2)<<endl;
            }
        }
    }
    
    return 0;
}