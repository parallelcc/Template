// Copyright 2016 Parallelc
#include <bits/stdc++.h>
using namespace std;  // NOLINT
using T = int;
const T INF = 0x3f3f3f3f;
struct node {
    int v;
    T w;
};
T spfa(vector<vector<node>>& lj, int S, int N) {
    int n = lj.size();
    static vector<T> dis;
    fill(dis.begin(), dis.end(), INF), dis.resize(n, INF);
    static vector<int> us, cnt, pre;
    fill(us.begin(), us.end(), 0), us.resize(n);
    fill(cnt.begin(), cnt.end(), 0), cnt.resize(n);
    pre.resize(n);
    us[S] = 1;
    dis[S] = 0;
    queue<int> q;
    q.push(S);
    cnt[S] = 1;
    pre[S] = -1;
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        us[now] = 0;
        for (auto& i : lj[now]) {
            if (dis[i.v] > dis[now] + i.w) {
                dis[i.v] = dis[now] + i.w;
                pre[i.v] = now;
                if (!us[i.v]) {
                    us[i.v] = 1;
                    q.push(i.v);
                    if (++cnt[i.v] > n) return -1;
                }
            }
        }
    }
    return dis[N];
}
