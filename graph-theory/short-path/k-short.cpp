#include <bits/stdc++.h>
using namespace std;
using LL = int64_t;
using T = int;
const T INF = 0x3f3f3f3f;
struct node {
    int v;
    T w, g;
    bool operator< (const node& e) const {return w > e.w;}
};
vector<T> dij(const vector<vector<node>>& lj, int S, int N) {
    int n = lj.size();
    vector<T> a(n, INF);
    a[S] = 0;
    priority_queue<node> q;
    q.push({S, 0});
    node mini;
    while (!q.empty()) {
        do {
            mini = q.top();
            q.pop();
        }while(mini.w > a[mini.v] && !q.empty());
        if (mini.w == a[mini.v]) {
            for (auto& i : lj[mini.v]) {
                T k = mini.w + i.w;
                if (a[i.v] > k) {
                    a[i.v] = k;
                    q.push({i.v, k});
                }
            }
        }
    }
    return a;
}

T kshort(vector<vector<node>>& lj, int S, int N, int k) {
    int n = lj.size();
    auto h = dij(lj, N, S);
    if (h[S] == INF) return INF;
    vector<int> num(n);
    node now = {S, h[S], 0};
    priority_queue<node> q;
    q.push(now);
    while (!q.empty()) {
        now = q.top();
        q.pop();
        num[now.v]++;
        if (num[N] == k) return now.w;
        if (num[now.v] > k) continue;
        for (auto& i : lj[now.v]) {
            node tmp;  // new node
            tmp.v = i.v;
            if (h[tmp.v] == INF) continue;
            tmp.g = now.g + i.w;
            tmp.w = tmp.g + h[tmp.v];
            q.push(tmp);
        }
    }
    return INF;
}
