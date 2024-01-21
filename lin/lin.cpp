#include <bits/stdc++.h>

using namespace std;

long long n,k;
pair<pair<long long, long long>, long long> tab[200007];
pair<long long, long long> tab2[200007];
set<long long> times;
map<long long, long long> scaled;
map<long long, long long> rescaled;
map<long long, long long> leftmost;
map<long long, long long> rightmost;
long long sz = 1;
long long bst[1100007];

queue<pair<long long, long long> > insert_q;
queue<pair<long long, long long> > delete_q;

void update(long long w) {
    bst[w] = bst[w * 2] + bst[w * 2 + 1];
    if(w > 1) {
        update(w / 2);
    }
}

long long query(long long w, long long p, long long q, long long a, long long b) {
    if(p >= a && q <= b) {
        return bst[w];
    }
    else if(q < a || p > b) {
        return 0;
    }
    else {
        return query(w * 2, p, (p + q) / 2, a, b) + query(w * 2 + 1, (p + q) / 2 + 1, q, a,b);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>k;

    for(long long i = 0; i < n; i++) {
        cin>>tab[i].first.first>>tab[i].first.second>>tab[i].second;
        tab2[i] = make_pair(tab[i].first.second, tab[i].second);
        times.insert(tab[i].second);
    }

    long long cnt = 0;
    for(auto i = times.begin(); i != times.end(); i++) {
        scaled[*i] = cnt;
        rescaled[cnt] = *i;
        cnt++;
    }

    while(sz < cnt) {
        sz*=2;
    }

    sort(tab, tab+n);
    sort(tab2, tab2+n);

    long long id = 0;
    long long id_left = 0;
    long long id_right = 0;
    while(id < cnt) {
        while(id_right+1 < cnt && abs(rescaled[id] - rescaled[id_right+1]) <= k) {
            id_right++;
        }

        while(id_left+1 < cnt && abs(rescaled[id] - rescaled[id_left]) > k) {
            id_left++;
        }

        leftmost[id] = min(id_left, id);
        rightmost[id] = max(id_right, id);
        id++;
    }

    for(long long i = 0; i < n; i++) {
        insert_q.push(make_pair(tab[i].first.first, scaled[tab[i].second]));
    }

    for(long long i = 0; i < n; i++) {
        delete_q.push(make_pair(tab2[i].first, scaled[tab2[i].second]));
    }

    pair<long long,long long> cur_pair;

    long long res = 0;
    while(!insert_q.empty()) {
        if(delete_q.front().first < insert_q.front().first) {
            cur_pair = delete_q.front();
            delete_q.pop();
            bst[sz + cur_pair.second]--;
            update((sz + cur_pair.second)/2);
        }
        else {
            cur_pair = insert_q.front();
            insert_q.pop();
            res += (long long)query(1, 1, sz, leftmost[cur_pair.second] + 1, rightmost[cur_pair.second] + 1);
            bst[sz + cur_pair.second]++;
            update((sz + cur_pair.second) / 2);
        }
    }

    cout<<res<<endl;

    return 0;
}