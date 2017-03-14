// Copyright 2017 Parallelc
#include <bits/stdc++.h>
using namespace std;  // NOLINT
vector<int> tarjan(const vector<vector<int>>& lj) {
    int n = lj.size();
    vector<int> dfn(n), low(n), add_block(n);
    int ind = 1;
    function<void(int, int)> dfs = [&](int k, int pre) {
        dfn[k] = low[k] = ind++;
        int son = 0;
        for (auto i : lj[k]) {
            if (!dfn[i]) {
                son++;
                dfs(i, k);
                low[k] = min(low[k], low[i]);
                // bridge - (i, k), (k, i)
                if (low[i] > dfn[k]) {
                    // todo
                }
                // not root - cut point
                if (k != pre && low[i] >= dfn[k]) {
                    add_block[k]++;
                }
            } else if (i != pre) {
                low[k] = min(low[k], dfn[i]);
            }
        }
        // root - cut point
        if (k == pre)
            add_block[k] = son - 1;
    };
    for (int i = 0; i < n; i++) {
        if (!dfn[i]) {
            ind = 1;
            dfs(i, i);
        }
    }
    return add_block;
}
