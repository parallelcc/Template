// Copyright 2017 Parallelc
#include <bits/stdc++.h>
using namespace std;  // NOLINT
using T = int;

vector<int> bcj;
int gr(int k) {
    return k == bcj[k]?k:bcj[k] = gr(bcj[k]);
}

struct node {
    int v;
    T w;
};
void LCA(vector<vector<node>>& lj, int r, vector<node>& p) {
    int n = lj.size(), q = p.size();
    vector<vector<node>> que(n);
    for (int i = 0; i < q; i++) {
        que[p[i].v].push_back({p[i].w, i});
        que[p[i].w].push_back({p[i].v, i});
    }
    bcj.resize(n);
    iota(bcj.begin(), bcj.end(), 0);
    vector<int> ans(q);
    vector<T> dis(n);
    function<void(int, int)> dfs = [&](int k, int pre) {
        for (auto& i : lj[k]) {
            if (i.v != pre) {
                dis[i.v] = dis[k] + i.w;
                dfs(i.v, k);
                bcj[i.v] = k;
            }
        }
        for (auto& i : que[k]) {
            if (bcj[i.v] != i.v || i.v == k) {
                ans[i.w] = gr(i.v);
            }
        }
    };
    dfs(r, r);
    // TODO(Parallelc)
}
